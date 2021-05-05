#include "MatcherAutomaton.h"
#include <iostream>
using namespace std;

MatcherAutomaton::MatcherAutomaton(string definition, TokenType tokenType)
{
    toMatch = definition;
    type = tokenType;
}
void MatcherAutomaton::S0(const std::string &input)
{
    bool isMatch = true;
    //cout << toMatch << endl;
    for(unsigned int i = 0; i < toMatch.size() && isMatch; i++) {
        if (input[i] != toMatch[i]) {
            isMatch = false;
            //cout << "input does not match" << endl;
        }
    }
    if(isMatch)
    {
        this->inputRead = toMatch.size();
        //cout << "Input Matches!" << endl;
    }


}

