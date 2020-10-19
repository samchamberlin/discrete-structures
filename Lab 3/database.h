#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <ctype.h>
#include <locale>
#include <iostream>
#include <set>
#include <map>
#include <iterator>

#include "token.h"
#include "parameter.h"
#include "tuple.h"
#include "scheme.h"
#include "relation.h"


class Database{

private:

    map<string, Relation> relations;

public:

    Database(){}
    ~Database(){}
    void populateDatabase(string name, Relation relation);
    void addTuples(string name, Tuple tuple);
    Relation getRelation(string name);

};
#endif
