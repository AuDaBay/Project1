#include <iostream>
#include <vector>
#include "Parser.h"
using namespace std;

Parser::Parser()
{

}
Parser::~Parser()
{

}

void Parser::Parse()
{
    try
    {
     parseDatalogProgram(tokenList);
    }
    catch(Token* error)
    {
        cout << "Failure!" << endl;
        cout<< "  "; error->toString();
    }
}
void Parser::parseDatalogProgram(vector<Token*> tokenList)
{
    currToken = tokenList[index];

    match(TokenType::SCHEMES);
    match(TokenType::COLON);
    parseScheme();
    parseSchemeList();
    match(TokenType::FACTS);
    match(TokenType::COLON);
    parseFactList();
    match(TokenType::RULES);
    match(TokenType::COLON);
    parseRuleList();
    match(TokenType::QUERIES);
    match(TokenType::COLON);
    parseQuery();
    parseQueryList();
    match(TokenType::END_OF_FILE);
    cout << "Success!" << endl;
    Lists.toString();
}
void Parser::parseFact()
{
    parameterList.clear();
    Predicate Fact;
    Parameter factParam;
    match(TokenType::ID);
    Fact.setID(prevToken->getVal());
    match(TokenType::LEFT_PAREN);
    match(TokenType::STRING);
    factParam.setString(prevToken->getVal());
    Lists.addSetString(prevToken->getVal());
    parameterList.push_back(factParam);
    parseStringList();
    match(TokenType::RIGHT_PAREN);
    match(TokenType::PERIOD);
    for(unsigned int i = 0; i < parameterList.size(); i++)
    {
        Fact.addParameter(parameterList.at(i));
    }

    Lists.addFact(Fact);

}
void Parser::parseFactList()
{
    if(currToken->getType() == TokenType::ID)
    {
        parseFact();
        parseFactList();
    }
}
void Parser::parseScheme()
{
    parameterList.clear();
    Parameter SchemeID;
    Predicate Scheme;
    match(TokenType::ID);
    Scheme.setID(prevToken->getVal());
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    SchemeID.setString(prevToken->getVal());
    parameterList.push_back(SchemeID);
    parseIDList();
    match(TokenType::RIGHT_PAREN);
    for(unsigned int i = 0; i < parameterList.size(); i++)
        {
            Scheme.addParameter(parameterList.at(i));
        }

    Lists.addScheme(Scheme);
}
void Parser::parseSchemeList()
{
    if(currToken->getType() == TokenType::ID)
    {
        parseScheme();
        parseSchemeList();
    }
}
void Parser::parseRule()
{
    if(currToken->getType() == TokenType::ID)
    {
        bodyPredicates.clear();
        Rule rule;
        rule.setHead(parseHeadPredicate());
        match(TokenType::COLON_DASH);
        rule.addBody(parsePredicate());
        parsePredicateList();
        match(TokenType::PERIOD);
        for(unsigned int i = 0; i < bodyPredicates.size(); i++)
        {
            rule.addBody(bodyPredicates.at(i));
        }

        Lists.addRule(rule);
    }
}
void Parser::parseRuleList()
{
    if(currToken->getType() == TokenType::ID)
    {
        parseRule();
        parseRuleList();
    }
}
void Parser::parseQuery()
{
    Predicate Query = parsePredicate(); //do we need to check here
    match(TokenType::Q_MARK);

    Lists.addQuery(Query);
}
void Parser::parseQueryList()
{
    if(currToken->getType() == TokenType::ID)
    {
        parseQuery();
        parseQueryList();
    }
}
void Parser::parseIDList()
{
    if(currToken->getType() == TokenType::COMMA)
    {
        match(TokenType::COMMA);
        match(TokenType::ID);
        Parameter IDListID;
        IDListID.setString(prevToken->getVal());
        parameterList.push_back(IDListID);
        parseIDList();
    }
}
Predicate Parser::parsePredicate()
{
    parameterList.clear();
    Predicate newPred;
    match(TokenType::ID);
    newPred.setID(prevToken->getVal());
    match(TokenType::LEFT_PAREN);
    parseParameter();
    parseParameterList();
    match(TokenType::RIGHT_PAREN);
    for(unsigned int i = 0; i < parameterList.size(); i++)
    {
        newPred.addParameter(parameterList.at(i));
    }
    return newPred;
}
Predicate Parser::parseHeadPredicate()
{
    parameterList.clear();
    Predicate headPred;
    Parameter headParam;
    match(TokenType::ID);
    headPred.setID(prevToken->getVal());
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    headParam.setString(prevToken->getVal());
    headPred.addParameter(headParam);
    parseIDList();
    match(TokenType::RIGHT_PAREN);
    for(unsigned int i = 0; i < parameterList.size(); i++)
    {
        headPred.addParameter(parameterList.at(i));
    }

    return headPred;
}
void Parser::parsePredicateList()
{
    if(currToken->getType() == TokenType::COMMA)
    {
        match(TokenType::COMMA);
        bodyPredicates.push_back(parsePredicate());
        parsePredicateList();
    }
}
void Parser::parseStringList()
{
    if(currToken->getType() == TokenType::COMMA)
    {
        Parameter stringID;
        match(TokenType::COMMA);
        match(TokenType::STRING);
        stringID.setString(prevToken->getVal());
        Lists.addSetString(prevToken->getVal());
        parameterList.push_back(stringID);
        parseStringList();
    }
}
void Parser::parseParameter()
{
    if(currToken->getType() == TokenType::STRING)
    {
        Parameter String;
        match(TokenType::STRING);
        String.setString(prevToken->getVal());
        //String.paraType = type::STRING;
        parameterList.push_back(String);
    }
    else if(currToken->getType() == TokenType::ID)
    {
        Parameter ID;
        match(TokenType::ID);
        ID.setString(prevToken->getVal());
        parameterList.push_back(ID);
    }
    else
    {
        cout << "incorrect" << endl;
    }
}
void Parser::parseParameterList()
{
    if(currToken->getType() ==  TokenType::COMMA)
    {
        match(TokenType::COMMA);
        parseParameter();
        parseParameterList();
    }
}
void Parser::match(TokenType token)
{
    if(currToken->getType() == token)
    {
        this->index++;
        currToken = tokenList[index];
        prevToken = tokenList[index - 1];
    }
    else
    {
        throw currToken;
    }
}

