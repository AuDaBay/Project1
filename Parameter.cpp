#include "Parameter.h"

void Parameter::setString(string input)
{
    parameter = input;
}

string Parameter::getVal()
{
    return parameter;
}

void Parameter::isConst()
{
    if(paraType == type::STRING)
    {
        isConstant = true;
    }
}