#include "predicate.h"

Predicate::Predicate(){
    ID = "";
    PARAMLIST = vector<Parameter>();
}

Predicate::Predicate(string id){
    ID = id;
    PARAMLIST = vector<Parameter>();
}

Predicate::Predicate(string id, vector<Parameter> paramlist){
    ID = id;
    PARAMLIST = paramlist;
}

Predicate::~Predicate(){}

string Predicate::getID(){
        return ID;
}

void Predicate::setID(string id){
    ID = id;
}

vector<Parameter> Predicate::getParameters(){
        return PARAMLIST;
}

void Predicate::addParameter(Parameter param){
        PARAMLIST.push_back(param);
}

string Predicate::toString(){
        stringstream ss;
        ss << ID << "(";
        for(int i = 0; i < (int)PARAMLIST.size(); i++){
                if(i == 0){
                        ss << PARAMLIST[i].toString();
                }else{
                        ss << "," << PARAMLIST[i].toString();
                }
        }
        ss << ")";
        return ss.str();
}

void Predicate::clearPredicate(){
    ID = "";
    PARAMLIST.clear();
}
