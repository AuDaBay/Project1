#ifndef PROJECT1_IDAUTOMATON_H
#define PROJECT1_IDAUTOMATON_H
#include "Automaton.h"
#include <string>
using namespace std;

class IDAutomaton: public Automaton
{
public:
    IDAutomaton();
    void S0(const std::string &input); //may need to switch it back to void
};




#endif //PROJECT1_IDAUTOMATON_H
