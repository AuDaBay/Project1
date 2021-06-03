#ifndef PROJECT1_INTERPRETER_H
#define PROJECT1_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter{
public:
    Interpreter(Datalog dataL);
    Relation evaluatePredicate(Predicate query);
    void SchemeIntoDataB(vector<Predicate> Schemes);
    void FactsIntoDataB(vector<Predicate> Facts);
    void evaluateRules(vector<Rule> Rules);
    void EvaluateQueries(vector<Predicate> Queries);
    void toString();
private:
    Datalog datalog;
    Database dataBase;
};


#endif //PROJECT1_INTERPRETER_H
