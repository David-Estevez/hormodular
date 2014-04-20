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
    const std::string GAIT_TABLE_FILEPATH = "../../data/test/test_gait_table.txt";
    //const std::string GAIT_TABLE_FILEPATH = "../data/test/test_gait_table.txt";
    gaitTable = new GaitTable(GAIT_TABLE_FILEPATH);

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

    delete gaitTable;
    gaitTable = NULL;
}

bool hormodular::Module::reset()
{
   id = (unsigned long) -1;
   configurationId = -1;
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
    std::stringstream  configurationIdStr;
    configurationIdStr << configurationId;

    if (headModule)
    {
        //-- Generate head hormones to tell the other modules who the hell are they
        for (int i = 0; i < (int) activeConnectors.size(); i++)
            activeConnectors[i]->outputBuffer.push_back( Hormone( activeConnectorsIndex[i],
                                                                  Hormone::HEAD_HORMONE,
                                                                  configurationIdStr.str()));
    }
    else
    {
        std::vector<int> headHormoneReceivedConnectors;
        std::vector<int> headHormoneNotReceivedConnectors;

        //-- If there is any head hormone
        for (int i = 0; i < (int) activeConnectors.size(); i++)
            for (int j = 0; j < (int) activeConnectors[i]->inputBuffer.size(); j++)
                if ( activeConnectors[i]->inputBuffer[j].getType() == Hormone::HEAD_HORMONE )
                {
                    headHormoneReceivedConnectors.push_back(i);

                    configurationId = atoi(activeConnectors[i]->inputBuffer[j].getData().c_str());
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
                Connector * outputConnector = activeConnectors[headHormoneNotReceivedConnectors[i]];
                outputConnector->outputBuffer.push_back( Hormone( activeConnectorsIndex[headHormoneNotReceivedConnectors[i]],
                                                                   Hormone::HEAD_HORMONE,
                                                                   configurationIdStr.str()));
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
    std::vector<float> parameters = gaitTable->getParameters(id);
    oscillator->setParameters(parameters[0], parameters[1], parameters[2], 1000);

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
