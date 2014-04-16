#include "Hormone.hpp"

hormodular::Hormone::Hormone(int sourceConnector, int type)
{
    this->sourceConnector = sourceConnector;
    this->type = type;
    data = "";
}

hormodular::Hormone::Hormone(int sourceConnector, int type, std::string data)
{
    this->sourceConnector = sourceConnector;
    this->type = type;
    this->data = data;
}

int hormodular::Hormone::getType()
{
    return type;
}

int hormodular::Hormone::getSourceConnector()
{
    return sourceConnector;
}

std::string hormodular::Hormone::getData()
{
    return data;
}
