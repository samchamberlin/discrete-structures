#include "datalog.h"

Datalog::Datalog(){
    SCHEMES = vector<Predicate>();
    FACTS = vector<Predicate>();
    RULES = vector<Rule>();
    QUERIES = vector<Predicate>();
    DOMAIN = set<string>();
}

Datalog::~Datalog(){}

void Datalog::addScheme(Predicate s){
        SCHEMES.push_back(s);
}

void Datalog::addFact(Predicate fact){
        FACTS.push_back(fact);
}

void Datalog::addRule(Rule rule){
        RULES.push_back(rule);
}

void Datalog::addQuery(Predicate query){
        QUERIES.push_back(query);
}

void Datalog::addDomain(string domain_string){
        DOMAIN.insert(domain_string);
}

string Datalog::stringSchemes(){
        stringstream ss;
        ss << "Schemes(" << SCHEMES.size() << "):";
        for(int i = 0; i < (int)SCHEMES.size(); i++)
                ss << "\n  " << SCHEMES[i].toString();
        return ss.str();
}

string Datalog::stringDomain(){
        stringstream ss;
        ss << "Domain(" << DOMAIN.size() << "):";
        set<string>::iterator myIterator;
        for(myIterator = DOMAIN.begin(); myIterator != DOMAIN.end(); myIterator++){
                ss << "\n  " << (*myIterator);
        }
        return ss.str();
}

string Datalog::stringFacts(){
        stringstream ss;
        ss << "Facts(" << FACTS.size() << "):";
        for(int i = 0; i < (int)FACTS.size(); i++)
                ss << "\n  " << FACTS[i].toString() << ".";
        return ss.str();
}

string Datalog::stringQueries(){
        stringstream ss;
        ss << "Queries(" << QUERIES.size() << "):";
        for(int i = 0; i < (int)QUERIES.size(); i++)
                ss << "\n  " << QUERIES[i].toString() << "?";
        return ss.str();
}

string Datalog::stringRules(){
        stringstream ss;
        ss << "Rules(" << RULES.size() << "):";
        for(int i = 0; i < (int)RULES.size(); i++)
                ss << "\n  " << RULES[i].toString();
        return ss.str();
}

string Datalog::toString(){
        stringstream ss;
        ss << endl << stringSchemes();
        ss << endl << stringFacts();
        ss << endl << stringRules();
        ss << endl << stringQueries();
        ss << endl << stringDomain();
        return ss.str();
}

vector<Predicate> Datalog::getSchemes(){
    return SCHEMES;
}

vector<Predicate> Datalog::getQueries(){
    return QUERIES;
}

vector<Predicate> Datalog::getFacts(){
    return FACTS;
}

vector<Rule> Datalog::getRules(){
    return RULES;
}

set<string> Datalog::getDomains(){
    return DOMAIN;
}
