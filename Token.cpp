#include "Token.h"
#include <iostream>
using namespace std;
string tokenToString(TokenType type)
{
    switch(type) {
        case TokenType::COMMA: return "COMMA"; break;
        case TokenType::PERIOD: return "PERIOD"; break;
        case TokenType::Q_MARK: return "Q_MARK"; break;
        case TokenType::LEFT_PAREN: return "LEFT_PAREN"; break;
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN"; break;
        case TokenType::COLON: return "COLON"; break;
        case TokenType::COLON_DASH: return "COLON_DASH"; break;
        case TokenType::MULTIPLY: return "MULTIPLY"; break;
        case TokenType::ADD: return "ADD"; break;
        case TokenType::SCHEMES: return "SCHEMES"; break;
        case TokenType::FACTS: return "FACTS"; break;
        case TokenType::RULES: return "RULES"; break;
        case TokenType::QUERIES: return "QUERIES"; break;
        case TokenType::ID: return "ID"; break;
        case TokenType::STRING: return "STRING"; break;
        case TokenType::COMMENT: return "COMMENT"; break;
        case TokenType::END_OF_FILE: return "EOF"; break;
        case TokenType::UNDEFINED: return "UNDEFINED"; break;
        default: return "Not a tokenType"; break;
    }
}
Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    actVal = description;
    lineNum = line;
    tokenType = type;
}
void Token::toString()
{
    cout << "(" << tokenToString(tokenType) << "," << "\"" << actVal <<"\"" << "," << lineNum << ")" << endl;
}
TokenType Token::getType()
{
    return tokenType;
}
string Token::getVal()
{
    return actVal;
}
