#include "IDAutomaton.h"
using namespace std;

IDAutomaton::IDAutomaton()
{
    this->type = TokenType::ID;
}
void IDAutomaton::S0(const std::string &input)
{
    bool isID = false;
    inputRead = 0;
    if(isalpha(input[0]))
    {
        isID = true;
        inputRead++;
    }
    if(isID)
    {
        for(unsigned int i = 1; i < input.size(); i++)
        {
            if(isalnum(input[i]))
            {
                inputRead++;
            }
            else
            {
                break;
            }
        }
    }
}