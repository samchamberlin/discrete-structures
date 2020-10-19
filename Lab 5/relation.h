#ifndef RELATION_H
#define RELATION_H

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
#include "predicate.h"
#include "tuple.h"
#include "scheme.h"
#include "rule.h"

using namespace std;

class Relation{

private:

    string NAME;
    Scheme HEADERS;
    set<Tuple> DATA;

public:

    Relation(){}
    Relation(string name);
    Relation(string name, Scheme headers);
    Relation(string name, Scheme headers, set<Tuple> data);
    ~Relation();

    Relation select(string val, int col);
    Relation select(int column1, int column2);
    Relation project(vector<int> columnsToKeep);
    void rename(Scheme sch);
    void addTuple(Tuple tuple);
    set<Tuple> getData();
    Scheme getHeaders();
    void outputQuery(bool isEmpty, Predicate query);
    void unionAdd(Relation finalRelation);
    Relation join(Relation r);
    Scheme joinSchemes(vector<pair<int, int>> &matchingColumns, Scheme schemesR2);
    Tuple joinTuples(Tuple t1, Tuple t2, set<int> matchingColumnsSet);
    bool joinable(Tuple t1, Tuple t2, vector<pair<int, int>> matchingColumns);
    void outputRelation();

};

#endif
