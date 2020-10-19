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

};

#endif
