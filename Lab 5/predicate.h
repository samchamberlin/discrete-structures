#ifndef PREDICATE_H
#define PREDICATE_H

#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <ctype.h>
#include <locale>
#include "token.h"
#include "parameter.h"

class Predicate{

public:

    Predicate();
    Predicate(string id);
    Predicate(string id, vector<Parameter> paramlist);
    ~Predicate();

    string ID;
    vector<Parameter> PARAMLIST;
    string getID();
    void setID(string id);
    vector<Parameter> getParameters();
    void addParameter(Parameter param);
    string toString();
    void clearPredicate();

};

#endif
