#include "CommentAutomaton.h"
using namespace std;

CommentAutomaton::CommentAutomaton()
{
    this->type = TokenType::COMMENT;
}
void CommentAutomaton::S0(const std::string &input)
{
    bool isLineComment = false;
    bool isBlockComment = false;
    if(input[0] == '#')
    {
        isLineComment = true;
        if(input[1] == '|')
        {
            isBlockComment = true;
            isLineComment = false;
        }
    }
    if(isBlockComment)
    {
        inputRead = 2;
        bool isValidComment = false;
        for(unsigned int i = 2; i < input.size(); i++)
        {
            inputRead++;
            if(input[i] == '\n')
            {
                newLines++;
            }
            if(input[i] == '|')
            {
                if((i < input.size() - 1) && (input[i+1] == '#'))
                {
                    inputRead++;
                    isValidComment = true;
                    break;
                }
            }
        }
        if(!isValidComment)
        {
            this->type = TokenType::UNDEFINED;
        }
    }
    if(isLineComment)
    {
        inputRead = 1;
        for(unsigned int i = 1; i < input.size(); i++)
        {
            if(input[i] == '\n')
            {
                break;
            }
            else
            {
                inputRead++;
            }
        }
    }
}