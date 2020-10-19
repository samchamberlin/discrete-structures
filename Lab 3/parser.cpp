#include "parser.h"

Parser::Parser(vector<Token> in){
    my_tokens = in;
    index = 0;
}

Parser::~Parser(){}

Token Parser::getCurrentToken(){
    return my_tokens[index];
}

Token Parser::peekNextToken(){
    return my_tokens[index + 1];
}

void Parser::parse(){
    Token currentToken = getCurrentToken();
    try{
        datalogProgram();
    }
    catch(Token currentToken){
    }
}

void Parser::datalogProgram(){
    match(SCHEMES);
    match(COLON);
    scheme();
    schemeList();
    match(FACTS);
    match(COLON);
    factList();
    match(RULES);
    match(COLON);
    ruleList();
    match(QUERIES);
    match(COLON);
    query();
    queryList();
    match(MY_EOF);
}

void Parser::match(TokenType expected){
    Token currentToken = getCurrentToken();
    if (expected == currentToken.getTokenType()){
        ++index;
    }
    else{
        throw currentToken;
    }
}

Datalog Parser::returnDatalog(){
    return d;
}

void Parser::schemeList(){
    Token currentToken = getCurrentToken();
    if(currentToken.getTokenType() == ID){
        scheme();
        schemeList();
    }
    else{
        return; //lambda
    }
}

void Parser::factList(){
    Token currentToken = getCurrentToken();
    if(currentToken.getTokenType() == ID){
        fact();
        factList();
    }
    else{
        return; //lambda
    }
}

void Parser::ruleList(){
    Token currentToken = getCurrentToken();
    if(currentToken.getTokenType() == ID){
        rule();
        ruleList();
    }
    else{
        return; //lambda
    }
}

void Parser::queryList(){
    Token currentToken = getCurrentToken();
    if(currentToken.getTokenType() == ID){
        tempPredicate.clearPredicate();
        query();
        tempPredicate.clearPredicate();
        queryList();
    }
    else{
        return; //lambda
    }
}


void Parser::scheme(){
    headPredicate();
    d.addScheme(tempPredicate);
    tempPredicate.clearPredicate();
}

void Parser::fact(){
    Token currentToken = getCurrentToken();
    tempPredicate = Predicate(currentToken.getTokenValue());
    match(ID);
    match(LEFT_PAREN);
    currentToken = getCurrentToken();
    Parameter tempParam = Parameter(MY_STRING, currentToken.getTokenValue());
    tempPredicate.addParameter(tempParam);
    d.addDomain(currentToken.getTokenValue());
    match(STRING);
    stringList();
    match(RIGHT_PAREN);
    match(PERIOD);
    d.addFact(tempPredicate);
    tempPredicate.clearPredicate();
}

void Parser::rule(){
    Token currentToken = getCurrentToken();
    r.clearVector();
    r.addHeadPredicate(headPredicate());
    tempPredicate.clearPredicate();
    match(COLON_DASH);
    r.addPredicate(predicate());
    tempPredicate.clearPredicate();
    predicateList();
    match(PERIOD);
    d.addRule(r);
}

void Parser::query(){
    Token currentToken = getCurrentToken();
    if(currentToken.getTokenType() == ID){
        tempPredicate = Predicate(predicate());
        match(Q_MARK);
        d.addQuery(tempPredicate);
        tempPredicate.clearPredicate();
    }
    else{
        return; //lambda
    }
}

Predicate Parser::headPredicate(){
    Token currentToken = getCurrentToken();
    string tempID1;
    string tempID2;
    string tempIDList;
    tempPredicate = Predicate(currentToken.getTokenValue());
    match(ID);
    match(LEFT_PAREN);
    currentToken = getCurrentToken();
    Parameter tempParam = Parameter(MY_ID, currentToken.getTokenValue());
    tempPredicate.addParameter(tempParam);
    match(ID);
    idList();
    match(RIGHT_PAREN);
    return tempPredicate;
}

Predicate Parser::predicate(){
    Token currentToken = getCurrentToken();
    string tempID1;
    Parameter tempParam;
    tempID1 = currentToken.getTokenValue();
    tempPredicate.setID(tempID1);
    match(ID);
    match(LEFT_PAREN);
    tempParameter = parameter();
    tempPredicate.addParameter(tempParameter);
    parameterList();
    match(RIGHT_PAREN);
    return tempPredicate;
}


void Parser::predicateList(){
    Token currentToken = getCurrentToken();
    if(currentToken.getTokenType() == COMMA){
        match(COMMA);
        r.addPredicate(predicate());
        tempPredicate.clearPredicate();
        predicateList();
    }
    else{
        return; //lambda
    }
}

void Parser::parameterList(){
    Token currentToken = getCurrentToken();
    if(currentToken.getTokenType() == COMMA){
        match(COMMA);
        tempParameter = parameter();
        tempPredicate.addParameter(tempParameter);
        parameterList();
    }
    else{
        return; //lambda
    }
}

void Parser::stringList(){
    Token currentToken = getCurrentToken();
    vector<Parameter> my_parameters;
    if(currentToken.getTokenType() == COMMA){
        match(COMMA);
        currentToken = getCurrentToken();
        tempParameter = Parameter(MY_STRING, currentToken.getTokenValue());
        tempPredicate.addParameter(tempParameter);
        d.addDomain(currentToken.getTokenValue());
        match(STRING);
        stringList();
    }
    else{
        return; //lambda
    }
}

void Parser::idList(){
    Token currentToken = getCurrentToken();
    if(currentToken.getTokenType() == COMMA){
        match(COMMA);
        currentToken = getCurrentToken();
        tempParameter = Parameter(MY_ID, currentToken.getTokenValue());
        tempPredicate.addParameter(tempParameter);
        match(ID);
        idList();
    }
    else{
        return; //lambda
    }
}

Parameter Parser::parameter(){
    string tempString;
    string tempID;
    string tempExpression;
    Token currentToken = getCurrentToken();
    if(currentToken.getTokenType() == STRING){
        tempString = currentToken.getTokenValue();
        match(STRING);
        return Parameter(MY_STRING, tempString);
    }
    else if(currentToken.getTokenType() == ID){
        tempID = currentToken.getTokenValue();
        match(ID);
        return Parameter(MY_ID, tempID);
    }
    else{
        tempExpression = expression();
        return Parameter(MY_EXPRESSION, tempExpression);
    }
}


string Parser::expression(){
    stringstream ss;
    string tempOperator;
    Parameter tempParam;

    match(LEFT_PAREN);
    ss << "(";
    tempParam = parameter();
    ss << tempParam.toString();
    tempOperator = operatorFunction();
    ss << tempOperator;
    tempParam = parameter();
    ss << tempParam.toString();
    match(RIGHT_PAREN);
    ss << ")";
    return ss.str();
}

string Parser::operatorFunction(){
    Token currentToken = getCurrentToken();
    if(currentToken.getTokenType() == ADD){
        match(ADD);
        return "+";
    }
    else{
        match(MULTIPLY);
        return "*";
    }
}
