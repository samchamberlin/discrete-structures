#include "rule.h"

Rule::Rule(){}

Rule::Rule(Predicate head){
    HEADPREDICATE = head;
}

Rule::Rule(Predicate head, vector<Predicate> my_pred){
    HEADPREDICATE = head;
    my_predicates = my_pred;
}

Rule::~Rule(){}

void Rule::addHeadPredicate(Predicate head){
    HEADPREDICATE = head;
}

void Rule::addPredicate(Predicate pred){
    my_predicates.push_back(pred);
}

Predicate Rule::getHeadPredicate(){
    return HEADPREDICATE;
}

vector<Predicate> Rule::getPredicateList(){
    return my_predicates;
}

void Rule::clearVector(){
    my_predicates.clear();
}

string Rule::toString(){
    stringstream ss;
    ss << HEADPREDICATE.toString() << " :- ";
    for(int i = 0; i < (int)my_predicates.size(); i++)
    {
        if(i == 0) ss << my_predicates[i].toString();

        else ss << "," + my_predicates[i].toString();
    }
    ss << ".";
    return ss.str();
}
