#ifndef PROJECT1_PREDICATE_H
#define PROJECT1_PREDICATE_H
#include <vector>
#include "Parameter.h"
class Predicate
{
public:
    void setID(string ID);
    string getID();
    void addParameter(Parameter parameter);
    string toStringFacts();
    string toString();
    //string toStringQuery();

    vector<Parameter> parameters;
private:
    string ID;
};
#endif //PROJECT1_PREDICATE_H
