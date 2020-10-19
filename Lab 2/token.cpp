#include "token.h"

Token::Token(TokenType type, string Value, int LineNum){
    VALUE = Value;
    LINENUM = LineNum;
    TYPE = type;
}

TokenType Token::getTokenType(){
    return TYPE;
}

string Token::toString(){
    stringstream ss;
    ss << "(" << tokenTypeToString(TYPE) << "," << "\""<< VALUE << "\"" << "," << LINENUM << ")" << endl;
    return ss.str();
}

string tokenTypeToString(TokenType t) {
    switch(t) {
        case COMMA:
            return "COMMA";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case SCHEMES:
            return "SCHEMES";
        case FACTS:
            return "FACTS";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case ID:
            return "ID";
        case STRING:
            return "STRING";
        case COMMENT:
            return "COMMENT";
        case UNDEFINED:
            return "UNDEFINED";
        case MY_EOF:
            return "EOF";

        default:
            return "";
    }
}
