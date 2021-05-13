#include "DatalogProgram.h"
using namespace std;

vector<Predicate> Datalog::getSchemes()
{
    return Schemes;
}
vector<Predicate> Datalog::getFacts()
{
    return Facts;
}
vector<Predicate> Datalog::getQueries()
{
    return Queries;
}
vector<Rule> Datalog::getRules()
{
    return Rules;
}
void Datalog::addScheme(Predicate Scheme)
{
    Schemes.push_back(Scheme);
}
void Datalog::addFact(Predicate Fact)
{
    Facts.push_back(Fact);
}
void Datalog::addRule(Rule rule)
{
    Rules.push_back(rule);
}
void Datalog::addQuery(Predicate query)
{
    Queries.push_back(query);
}
void Datalog::addSetString(string str)
{
    Domain.insert(str);
}
void Datalog::toString()
{
    cout << "Schemes(" << Schemes.size() << "):" << endl;
    for(unsigned int i = 0; i  < Schemes.size(); i++)
    {
        cout << "  " << Schemes[i].toString() << endl;
    }
    cout << "Facts(" << Facts.size() << "):" << endl;
    for(unsigned int i = 0; i  < Facts.size(); i++)
    {
        cout << "  " << Facts[i].toString() << "." << endl;
    }
    cout << "Rules(" << Rules.size() << "):" << endl;
    for(unsigned int i = 0; i  < Rules.size(); i++)
    {
        cout << "  " << Rules[i].toString() << "." << endl;
    }
    cout << "Queries(" << Queries.size() << "):" << endl;
    for(unsigned int i = 0; i  < Queries.size(); i++)
    {
        cout << "  " << Queries[i].toString() << "?" << endl;
    }
    cout << "Domain(" << Domain.size() << "):" << endl;
    for(auto it = Domain.begin(); it != Domain.end(); it++)
    {
        cout << "  " << *it << endl;
    }
}