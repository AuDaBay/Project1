#ifndef PROJECT1_STRINGAUTOMATON_H
#define PROJECT1_STRINGAUTOMATON_H
#include "Automaton.h"
#include <string>
using namespace std;

class StringAutomaton: public Automaton
{
public:
    StringAutomaton();
    void S0(const std::string &input);
};
#endif //PROJECT1_STRINGAUTOMATON_H
