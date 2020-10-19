#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

enum TokenType{COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, MY_EOF};

class Token{

private:   

    TokenType TYPE;
    string VALUE;
    int LINENUM;

public:

    Token (TokenType type, string value, int lineNum);
    string toString();

};

string tokenTypeToString(TokenType t);
