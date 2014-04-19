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
   //! \todo parseHormones

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
                }
            }
            if (!foundPingHormone)
                tempID += 16 * pow( 17, i);

            connectors[i]->inputBuffer.clear();
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
        if ( connectors[i] != NULL )
        {
            connectors[i]->outputBuffer.push_back( Hormone( i, Hormone::PING_HORMONE ));
        }
        else
        {
            std::cerr << "[Module] Error ocurred when accesing connector " << i << ", conector doesn't exist."
                         << std::endl;
            return false;
        }

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
