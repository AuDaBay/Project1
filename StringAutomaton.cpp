#include "StringAutomaton.h"
#include <iostream>
using namespace std;

StringAutomaton::StringAutomaton()
{
    this->type = TokenType::STRING;
}
void StringAutomaton::S0(const std::string &input)
{
    this->inputRead = 0;
    bool isString = false;
    if(input[0] == '\'')
    {
        isString = true;
    }

    if(isString)
    {
        bool isValidString = false;
        inputRead = 1;
        for(unsigned int i = 1; i < input.size(); i++)
        {
            inputRead++;
            if(input[i] == '\n')
            {
                newLines++;
            }
            if(input[i] == '\'')
            {
                if((input[i+1] == '\'') && (i < input.size() - 1))
                {
                    //iterate over the second single-quote, add for it, and move on
                    i++;
                    inputRead++;
                }
                else
                {
                   isValidString = true;
                   break;
                }
            }
        }
        //How to generate undefined token
        if(!isValidString)
        {
            //doesn't have to switch back because you will reach EOF
            this->type = TokenType::UNDEFINED;
        }
    }

}