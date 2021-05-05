#include "Lexer.h"
#include <cctype>
#include <fstream>
#include <string>
#include <iostream>
#include "Token.h"
#include "MatcherAutomaton.h"

using namespace std;
int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();
    string inputFile;
    ifstream inp(argv[1], ifstream::in);
    inputFile = inp.get();
    while(inp.peek() != EOF)
    {
        inputFile += inp.get();
    }
    //cout << inputFile << endl;
    // TODO
    lexer->Run(inputFile);
    delete lexer;

    return 0;
}