#ifndef DATALOG_H
#define DATALOG_H

#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <ctype.h>
#include <locale>
#include <set>

#include "token.h"
#include "predicate.h"
#include "rule.h"

class Datalog{

public:

    Datalog();
    ~Datalog();

    vector<Predicate> SCHEMES;
    vector<Predicate> QUERIES;
    vector<Predicate> FACTS;
    vector<Rule> RULES;
    set<string> DOMAIN;
    void addScheme(Predicate s);
    void addFact(Predicate f);
    void addRule(Rule r);
    void addQuery(Predicate q);
    void addDomain(string domain_string);
    string stringSchemes();
    string stringFacts();
    string stringRules();
    string stringQueries();
    string stringDomain();
    string toString();

    vector<Predicate> getSchemes();
    vector<Predicate> getQueries();
    vector<Predicate> getFacts();
    vector<Rule> getRules();
    set<string> getDomains();

};

#endif
