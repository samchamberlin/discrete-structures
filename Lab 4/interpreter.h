#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <ctype.h>
#include <locale>
#include <set>
#include <iterator>

#include "token.h"
#include "parameter.h"
#include "tuple.h"
#include "scheme.h"
#include "database.h"
#include "datalog.h"
#include "predicate.h"

class Interpreter{

private:

    Datalog MY_DATALOG;
    Database MY_DATABASE;
    bool evaluateQueries;

public:

    Interpreter();
    Interpreter(Datalog my_datalog);
    ~Interpreter(){}

    void evaluatingQueries();
    void createRelations();
    void populateRelations();
    void answerQueries();
    Relation answerSingleQuery(Predicate pred);
    int answerRules();
    void evaluateRules();
    void evaluateSingleRule(Rule rule);

};

#endif
