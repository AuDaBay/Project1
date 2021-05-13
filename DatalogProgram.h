#ifndef PROJECT1_DATALOGPROGRAM_H
#define PROJECT1_DATALOGPROGRAM_H
#include <iostream>
#include <vector>
#include <set>
#include "Predicate.h"
#include "Rule.h"
using namespace std;

class Datalog
{
private:
    vector<Predicate> Schemes;
    vector<Predicate> Facts;
    vector<Predicate> Queries;
    vector<Rule> Rules;
    set<string> Domain;
public:
    vector<Predicate> getSchemes();
    vector<Predicate> getFacts();
    vector<Predicate> getQueries();
    vector<Rule> getRules();
    void addScheme(Predicate Scheme);
    void addFact(Predicate Fact);
    void addRule(Rule rule);
    void addQuery(Predicate query);
    void addSetString(string str);
    void toString();

};
#endif //PROJECT1_DATALOGPROGRAM_H
