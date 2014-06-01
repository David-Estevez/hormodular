#include "Connector.hpp"

hormodular::Connector::Connector()
{
    remoteConnector = NULL;
}

bool hormodular::Connector::connectTo(hormodular::Connector * remoteConnector)
{
    this->remoteConnector = remoteConnector;

    if (remoteConnector == NULL)
        return false;
    else
        return true;

}

bool hormodular::Connector::sendHormones()
{
    if (remoteConnector == NULL)
    {
        outputBuffer.clear();
        return false;
    }

    while(outputBuffer.size() > 0)
    {
        remoteConnector->addInputHormone(outputBuffer.back());
        outputBuffer.pop_back();
    }

    return true;
}

bool hormodular::Connector::addOutputHormone(Hormone outputHormone)
{
    outputBuffer.push_back(outputHormone);
    return true;
}

bool hormodular::Connector::clearInputBuffer()
{
    inputBuffer.clear();
    return true;
}

bool hormodular::Connector::addInputHormone(hormodular::Hormone inputHormone)
{
    inputBuffer.push_back(inputHormone);
    return true;
}

int hormodular::Connector::getLocalOrientation() const
{
    return localOrientation;
}

void hormodular::Connector::setLocalOrientation(int localOrientation)
{
    this->localOrientation = localOrientation;
}

std::vector<hormodular::Hormone> hormodular::Connector::getInputBuffer()
{
    return inputBuffer;
}

hormodular::Connector *hormodular::Connector::getRemoteConnector()
{
    return remoteConnector;
}

