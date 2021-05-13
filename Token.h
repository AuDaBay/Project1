#ifndef TOKEN_H
#define TOKEN_H
#include <string>
using namespace std;
enum class TokenType{
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    END_OF_FILE,
    UNDEFINED
};

class Token
{
private:
    // TODO: add member variables for information needed by Token
    string actVal;
    int lineNum;
    TokenType tokenType;
public:
    Token(TokenType type, std::string description, int line);
    void toString();
    TokenType getType();
    string getVal();
    // TODO: add other needed methods
};

#endif // TOKEN_H

