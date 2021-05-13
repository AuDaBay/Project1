#include "Predicate.h"
#include <iostream>
using namespace std;
void Predicate::setID(string name)
{
    ID =  name;
}
string Predicate::getID()
{
    return ID;
}
void Predicate::addParameter(Parameter parameter)
{
    parameters.push_back(parameter);
}
string Predicate::toStringFacts()
{
    string SchemeString;
    SchemeString += getID() + "(";

    for(unsigned int i = 0; i < parameters.size(); i++)
    {
        SchemeString += "\'" + parameters[i].getVal() + "\'" + ",";
    }
    SchemeString.pop_back();
    SchemeString += ")";

    return SchemeString;
}
string Predicate::toString()
{
    string SchemeString;
    SchemeString += getID() + "(";

    for(unsigned int i = 0; i < parameters.size(); ++i)
    {
        SchemeString += parameters[i].getVal() + ",";
    }
    SchemeString.pop_back();
    SchemeString += ")";

    return SchemeString;
}

