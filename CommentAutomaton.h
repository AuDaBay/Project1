
#ifndef PROJECT1_COMMENTAUTOMATON_H
#define PROJECT1_COMMENTAUTOMATON_H
#include "Automaton.h"
#include <string>
using namespace std;

class CommentAutomaton: public Automaton
{
public:
    CommentAutomaton();
    void S0(const std::string &input); //may need to be switched back to void
};
#endif //PROJECT1_COMMENTAUTOMATON_H
