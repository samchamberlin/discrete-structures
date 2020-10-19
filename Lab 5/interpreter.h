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
#include <stack>

#include "token.h"
#include "parameter.h"
#include "tuple.h"
#include "scheme.h"
#include "database.h"
#include "datalog.h"
#include "predicate.h"
#include "graph.h"
#include "node.h"
#include "graph.h"

class Interpreter{

private:

    Datalog MY_DATALOG;
    Database MY_DATABASE;
    bool evaluateQueries;
    Graph MY_GRAPH;
    Graph MY_REVERSE_GRAPH;
    stack<int> nodeStack;
    vector<set<int>> SCC;

public:

    Interpreter();
    Interpreter(Datalog my_datalog);
    ~Interpreter(){}

    void evaluatingQueries();
    void createRelations();
    void populateRelations();
    void answerQueries();
    Relation answerSingleQuery(Predicate pred);
    void answerRules();
    void evaluateRules();
    void evaluateSingleRule(Rule rule);
    void printSCC(set<int> mySCC);
    void fixedPoint(set<int> mySCC, int i);
    void dfsForest();
    void dfs(Node& node, int index);
    void dfsForestSCC();
    set<int> dfsSCC(Node& node, int index);
    void buildGraphs();

};

#endif
