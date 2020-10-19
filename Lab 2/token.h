#ifndef token_h
#define token_h

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

enum TokenType{
    /*
        This is used to compare tokens to each other. Instead of comparing strings,
        this allows me to compare integers. Speeds up run time.
    */
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY,
    ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, MY_EOF
};

class Token{

private:

    TokenType TYPE;
    string VALUE;
    int LINENUM;

public:

    Token (TokenType type, string value, int lineNum);
    string toString();
    TokenType getTokenType();
    string getTokenValue(){
        return VALUE;
    }

};

string tokenTypeToString(TokenType t);

#endif
