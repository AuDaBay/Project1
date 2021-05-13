#include "Rule.h"
#include <iostream>
using namespace std;

void Rule::setHead(Predicate head)
{
    headPredicate = head;
}
void Rule::addBody(Predicate body)
{
    bodyPredicates.push_back(body);
}
string Rule::toString()
{
    string ruleString;
    ruleString += headPredicate.toString() + " :- ";
    for(unsigned int i = 0; i < bodyPredicates.size(); i++)
    {
        ruleString += bodyPredicates[i].toString() + ",";
    }
    ruleString.pop_back();

    return ruleString;
}
