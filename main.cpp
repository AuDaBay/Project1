#include "Lexer.h"
#include <cctype>
#include <fstream>
#include <string>
#include <iostream>
#include "Token.h"
#include "MatcherAutomaton.h"
#include "Parser.h"
#include "Interpreter.h"

using namespace std;
int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();
    Parser* parser = new Parser();
    string inputFile;
    ifstream inp(argv[1], ifstream::in);
    //inputFile = inp.get();
    while(inp.peek() != EOF)
    {
        inputFile += inp.get();
    }
    //cout << inputFile << endl;
    // TODO
    parser->tokenList = lexer->Run(inputFile);
    Interpreter interpreter = Interpreter(parser->Parse());
    //interpreter->toString();
    delete lexer;

    return 0;
}