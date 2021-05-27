#ifndef PROJECT1_PARSER_H
#define PROJECT1_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Token.h"
#include "Parameter.h"
#include "DatalogProgram.h"
#include "Rule.h"
using namespace std;

class Parser
{
public:
    Parser();
    ~Parser();
    Datalog Parse();
    vector<Token*> tokenList;





private:
    int index = 0;
    Token* currToken = nullptr;
    Token* prevToken = nullptr;
    vector<Parameter> parameterList;
    vector<Predicate> bodyPredicates;
    Datalog Lists;

    void match(TokenType type);
    void parseDatalogProgram(vector<Token*> tokenList);
    void parseFact();
    void parseFactList();
    void parseScheme();
    void parseSchemeList();
    void parseRule();
    void parseRuleList();
    void parseQuery();
    void parseQueryList();
    void parseIDList();
    Predicate parsePredicate();
    Predicate parseHeadPredicate();
    void parsePredicateList();
    void parseStringList();
    void parseParameter();
    void parseParameterList();


};


#endif //PROJECT1_PARSER_H
