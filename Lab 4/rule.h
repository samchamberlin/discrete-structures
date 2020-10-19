
#ifndef RULE_H
#define RULE_H

#include "token.h"
#include "predicate.h"

class Rule{

private:

    Predicate HEADPREDICATE;
    vector<Predicate> my_predicates;

public:

    Rule();
    Rule(Predicate head);
    Rule(Predicate head, vector<Predicate> my_pred);
    ~Rule();

    void addHeadPredicate(Predicate head);
    void addPredicate(Predicate pred);
    vector<Predicate> getPredicateList();
    Predicate getHeadPredicate();
    void clearVector();
    string toString();

};

#endif
