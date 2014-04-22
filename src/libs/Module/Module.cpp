#include "Module.hpp"

hormodular::Module::Module(ConfigParser configParser)
{
    //-- Create connectors
    for(int i = 0; i < 4; i++)
        connectors.push_back(new Connector() );

    //-- Create sinusoidal oscillator
    oscillator = new SinusoidalOscillator();

    //-- Create gait table
    //! \todo Use configParser for this:
    //const std::string GAIT_TABLE_FILEPATH = "../../data/test/test_gait_table.txt";
    //const std::string GAIT_TABLE_FILEPATH = "../data/test/test_gait_table.txt";
    const std::string GAIT_TABLE_MULTIDOF_11 = "multidof-11-2-gaittable.txt";
    const std::string GAIT_TABLE_MULTIDOF_7 = "multidof-7-tripod-gaittable.txt";
    const std::string GAIT_TABLE_MULTIDOF_9 = "multidof-9-quad-gaittable.txt";


    gaitTables.push_back(new GaitTable(configParser.getGaitTableFolder() + GAIT_TABLE_MULTIDOF_11));
    gaitTables.push_back(new GaitTable(configParser.getGaitTableFolder() + GAIT_TABLE_MULTIDOF_7));
    gaitTables.push_back(new GaitTable(configParser.getGaitTableFolder() + GAIT_TABLE_MULTIDOF_9));

    //-- Load frequency table:
    frequencyTable = new GaitTable(configParser.getFrequencyTableFile());

    reset();
}

hormodular::Module::~Module()
{
    for(int i = 0; i < 4; i++)
    {
        delete connectors[i];
        connectors[i] = NULL;
    }

    delete oscillator;
    oscillator = NULL;

    for(int i = 0; i < (int)gaitTables.size(); i++)
    {
        delete gaitTables[i];
        gaitTables[i] = NULL;
    }

    delete frequencyTable;
    frequencyTable = NULL;
}

bool hormodular::Module::reset()
{
   id = (unsigned long) -1;
   configurationId = 0;
   currentJointPos = 0;
   elapsedTime = 0;

   return true;
}

bool hormodular::Module::attach(int localConnector, Connector *remoteConnector, int orientation)
{
    if (localConnector < 0 || localConnector >= (int) connectors.size())
    {
        std::cerr << "[Module] Error: could not attach to connector: " << localConnector << std::endl;
        return false;
    }

    connectors[localConnector]->remoteConnector = remoteConnector;

    //! \todo I should not take the orientation from the config file happily
    connectors[localConnector]->localOrientation = orientation;

    return true;
}

hormodular::Connector *hormodular::Module::getConnector(int localConnector)
{
    if (localConnector < 0 || localConnector >= 4)
    {
        std::cerr << "[Module] Error: could not get connector: " << localConnector << std::endl;
        return NULL;
    }
    else
    {
        return connectors[localConnector];
    }
}

bool hormodular::Module::processHormones()
{
    //-- Ping Hormones processing & sending
    //-----------------------------------------------------------------------------------------------------
    std::vector<Connector *> activeConnectors;
    std::vector<int> activeConnectorsIndex;

    //-- Find local ID from "Ping" hormones
    unsigned int tempID = 0;

    for (int i = 0; i < (int) connectors.size(); i++)
        if ( connectors[i] != NULL )
        {
            bool foundPingHormone = false;

            for (int j = 0; j < (int) connectors[i]->inputBuffer.size(); j++)
            {
                if ( connectors[i]->inputBuffer[j].getType() == Hormone::PING_HORMONE )
                {
                    Hormone pingHormone = connectors[i]->inputBuffer[j];
                    tempID += (pingHormone.getSourceConnector() + connectors[i]->localOrientation* 4) * pow(17, i);

                    foundPingHormone = true;
                    activeConnectorsIndex.push_back(i);
                    activeConnectors.push_back(connectors[i]);

                    break;
                }
            }
            if (!foundPingHormone)
                tempID += 16 * pow( 17, i);
        }
        else
        {
            std::cerr << "[Module] Error ocurred when accesing connector " << i << ", conector doesn't exist."
                         << std::endl;
            return false;
        }

    id = tempID;

    //-- Set ping hormones on the outputBuffer of the connectors
    for (int i = 0; i < (int) connectors.size(); i++)
            connectors[i]->outputBuffer.push_back( Hormone( i, Hormone::PING_HORMONE ));


    //-- Leg hormones processing & sending
    //-------------------------------------------------------------------------------------------------------
    std::vector<int> legHormoneReceivedConnectors;
    std::vector<int> legHormoneNotReceivedConnectors;
    bool headModule = false;
    bool legModule = false;

    for (int i = 0; i < (int) activeConnectors.size(); i++)
        for (int j = 0; j < (int) activeConnectors[i]->inputBuffer.size(); j++)
            if ( activeConnectors[i]->inputBuffer[j].getType() == Hormone::LEG_HORMONE )
            {
                legHormoneReceivedConnectors.push_back(i);
                break;
            }
            else
            {
                legHormoneNotReceivedConnectors.push_back(i);
                break;
            }


    //-- Set leg hormones on the outputBuffer of the connectors
    if( activeConnectors.size() != 0 )
    {
        if ( activeConnectors.size() == 1)
        {
            //-- This case is for the 'leg' modules, that have to generate the leg hormone flux
	    std::cout << "Hey, I'm a leg module! (I am module with id: " << id << ")" << std::endl;
	    legModule = true;

            activeConnectors[0]->outputBuffer.push_back( Hormone( activeConnectorsIndex[0], Hormone::LEG_HORMONE ));
        }
        else if ( activeConnectors.size() == legHormoneReceivedConnectors.size() )
        {
            //-- If a module receives 'leg' hormones in all its active connectors, it is the head module
            std::cout << "Hey, I'm the head module! (I am module with id: " << id << ")" << std::endl;
            headModule = true;

            if (legHormoneReceivedConnectors.size() == 2)
            {
                std::cout << "I'm MultiDof-11-2!" << std::endl;
                configurationId = 0;
            }
            else if ( legHormoneReceivedConnectors.size() == 3 )
            {
                std::cout << "I'm MultiDof-7-Tripod!" << std::endl;
                configurationId = 1;
            }
            else if ( legHormoneReceivedConnectors.size() == 4 )
            {
                std::cout << "I'm MultiDof-9-Quad!" << std::endl;
                configurationId = 2;
            }
        }
        else if ( legHormoneReceivedConnectors.size() > 0)
        {
            //-- Otherwise, relay the hormones in all the active connectors that didn't receive leg hormones
            for (int i = 0; i < (int) legHormoneNotReceivedConnectors.size(); i++)
                activeConnectors[legHormoneNotReceivedConnectors[i]]->outputBuffer.push_back(
                            Hormone( activeConnectorsIndex[legHormoneNotReceivedConnectors[i]], Hormone::LEG_HORMONE ));

        }
    }


    //-- "Head" modules
    //-------------------------------------------------------------------------------------------------------
    if (headModule)
    {
        //-- Generate head hormones to tell the other modules who the hell are they
        for (int i = 0; i < (int) activeConnectors.size(); i++)
        {
            std::stringstream  configurationIdStr;
            configurationIdStr << configurationId;
            configurationIdStr << " " << activeConnectorsIndex[i];

            activeConnectors[i]->outputBuffer.push_back( Hormone( activeConnectorsIndex[i],
                                                                  Hormone::HEAD_HORMONE,
                                                                  configurationIdStr.str()));
        }
    }
    else
    {
        std::vector<int> headHormoneReceivedConnectors;
        std::vector<int> headHormoneNotReceivedConnectors;
        std::string hormoneData;
        std::vector<std::string> splitHormoneData;

        //-- If there is any head hormone
        for (int i = 0; i < (int) activeConnectors.size(); i++)
            for (int j = 0; j < (int) activeConnectors[i]->inputBuffer.size(); j++)
                if ( activeConnectors[i]->inputBuffer[j].getType() == Hormone::HEAD_HORMONE )
                {
                    headHormoneReceivedConnectors.push_back(i);

                    hormoneData = activeConnectors[i]->inputBuffer[j].getData();
                    splitHormoneData = splitString(hormoneData);

                    configurationId = atoi(splitHormoneData[0].c_str());

                    if (legModule)
                        id = 83521 + atoi(splitHormoneData[1].c_str());

                    break;
                }
                else
                {
                    headHormoneNotReceivedConnectors.push_back(i);
                    break;
                }

        if( headHormoneReceivedConnectors.size() > 0 )
            for (int i = 0; i < (int) headHormoneNotReceivedConnectors.size(); i++)
            {                
                if ( configurationId == 0 && ( id == 31466 || id == 30752) )
                {
                    std::stringstream  configurationIdStr;
                    configurationIdStr << configurationId;
                    configurationIdStr << " " << i + atoi(splitHormoneData[1].c_str());
                    hormoneData = configurationIdStr.str();
                }

                Connector * outputConnector = activeConnectors[headHormoneNotReceivedConnectors[i]];
                outputConnector->outputBuffer.push_back( Hormone( activeConnectorsIndex[headHormoneNotReceivedConnectors[i]],
                                                                  Hormone::HEAD_HORMONE,
                                                                  hormoneData));
            }

    }


    //-- Clean input buffers
    for (int i = 0; i < (int) connectors.size(); i++)
        connectors[i]->inputBuffer.clear();

    std::cout << "[Debug] Id: " << id << "-> " << configurationId << std::endl;

   return true;
}

bool hormodular::Module::sendHormones()
{
    for(int i = 0; i < (int) connectors.size(); i++)
        if ( connectors[i]->remoteConnector != NULL )
            while(connectors[i]->outputBuffer.size() > 0)
            {
                connectors[i]->remoteConnector->inputBuffer.push_back( connectors[i]->outputBuffer.back());
                connectors[i]->outputBuffer.pop_back();
            }
        else
            connectors[i]->outputBuffer.clear();

    return true;
}

bool hormodular::Module::updateOscillatorParameters()
{
    //! \todo Use a variable value for PERIOD of the oscillator
    std::vector<float> parameters = gaitTables[configurationId]->getParameters(id);
    int period = (int) ( 1000.0 / frequencyTable->getParameters(configurationId)[0]);
    oscillator->setParameters(parameters[0], parameters[1], parameters[2], period);

    return true;
}

float hormodular::Module::calculateNextJointPos()
{
    currentJointPos = oscillator->calculatePos(elapsedTime);
    return currentJointPos;
}

bool hormodular::Module::updateElapsedTime(int timeIncrement_ms)
{
    elapsedTime+=timeIncrement_ms;
    return true;
}

unsigned long hormodular::Module::getID()
{
    return id;
}

float hormodular::Module::getCurrentJointPos()
{
    return currentJointPos;
}

std::vector<std::string> hormodular::Module::splitString(std::string stringToSplit)
{
    /*
      This code has been copied from: http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
      */
    std::vector<std::string> tokens;
    std::istringstream iss(stringToSplit);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string> >(tokens));
    return tokens;

}
