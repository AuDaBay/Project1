#ifndef PROJECT1_MATCHERAUTOMATON_H
#define PROJECT1_MATCHERAUTOMATON_H
#include "Automaton.h"
class MatcherAutomaton: public Automaton
{
private:
    string toMatch;
    int newLines = 0;
public:
    MatcherAutomaton(string toMatch, TokenType tokenType);
    void S0(const std::string &input);
    int getNewLines() {return this->newLines;}
};



#endif //PROJECT1_MATCHERAUTOMATON_H
