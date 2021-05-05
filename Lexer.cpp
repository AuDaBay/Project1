#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
    for(unsigned int i = 0; i < automata.size(); i++)
    {
        delete automata[i];
    }
    for(unsigned int i = 0; i < tokens.size(); i++)
    {
        delete tokens[i];
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new MatcherAutomaton(",", TokenType::COMMA));
    automata.push_back(new MatcherAutomaton(".", TokenType::PERIOD));
    automata.push_back(new MatcherAutomaton("?", TokenType::Q_MARK));
    automata.push_back(new MatcherAutomaton("(", TokenType::LEFT_PAREN));
    automata.push_back(new MatcherAutomaton(")", TokenType::RIGHT_PAREN));
    automata.push_back(new MatcherAutomaton(":", TokenType::COLON));
    automata.push_back(new MatcherAutomaton(":-", TokenType::COLON_DASH));
    automata.push_back(new MatcherAutomaton("*", TokenType::MULTIPLY));
    automata.push_back(new MatcherAutomaton("+", TokenType::ADD));
    automata.push_back(new MatcherAutomaton("Schemes", TokenType::SCHEMES));
    automata.push_back(new MatcherAutomaton("Facts", TokenType::FACTS));
    automata.push_back(new MatcherAutomaton("Rules", TokenType::RULES));
    automata.push_back(new MatcherAutomaton("Queries", TokenType::QUERIES));
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
}

void Lexer::Run(std::string& input)
{
    // TODO: convert this pseudo-code with the algorithm into actual C++ code

    //set lineNumber to 1
    int lineNum = 1;
    // While there are more characters to tokenize
    while (input.size() > 0) {
        int maxRead = 0;
    // initialize maxAutomaton to be the first on in the list
        Automaton *maxAutomaton = automata.at(0);
 // TODO: you need to handle whitespace inbetween tokens
        if(isspace(input[0]))
        {
            while(isspace(input[0]) && input.size() > 1)
            {
                if(input[0] == '\n')
                {
                    lineNum++;
                }
                input = input.substr(1);
            }
        }
        if(input.size() == 1 && isspace(input[0]))
        {
            if(input[0] == '\n')
            {
                lineNum++;
            }
            input = "";
            break;
        }
        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        for(int i = 0; i < automata.size(); i++)
        {
            int inputRead = automata.at(i)->Start(input);
            if (inputRead > maxRead)
            {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }
        // Here is the "Max" part of the algorithm
        if (maxRead > 0)
        {

            Token* newToken = maxAutomaton->CreateToken(input.substr(0,maxRead), lineNum);
            lineNum += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            //set maxRead to 1
            maxRead = 1;
            //set newToken to a  new undefined Token (with first character of input)
            Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0, maxRead), lineNum);
            //add newToken to collection of all tokens
            tokens.push_back(newToken);
        }
        // Update `input` by removing characters read to create Token
        //remove maxRead characters from input
        input = input.substr(maxRead);
    }
    //add end of file token to all tokens
    //lineNum++; //may need to fix
    Token* eofTok = new Token(TokenType::END_OF_FILE, "", lineNum);
    tokens.push_back(eofTok);

    toString();
}

void Lexer::toString()
{
    for(unsigned int i = 0; i < tokens.size(); i++)
    {
        tokens.at(i)->toString();
    }
    cout << "Total Tokens = " << tokens.size();
}


