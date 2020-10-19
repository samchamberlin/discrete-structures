#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <ctype.h>
#include <locale>
#include "token.h"
#include "datalog.h"

using namespace std;

class Parser{

private:

    vector<Token> my_tokens;
    int index;
    Datalog d;
    Rule r;
    vector<Parameter> tempParamList;
    string privateTempIDList;
    Predicate tempPredicate;
    Parameter tempParameter;

public:

    Parser(vector<Token>);
    ~Parser();
    Token getCurrentToken();
    Token peekNextToken();
    void parse();
    void datalogProgram();
    void match(TokenType expected);
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    Predicate headPredicate();
    Predicate predicate();
    void predicateList();
    void parameterList();
    void stringList();
    void idList();
    Parameter parameter();
    string expression();
    string operatorFunction();

};

#endif
