#include "interpreter.h"

Interpreter::Interpreter(Datalog my_datalog){
    MY_DATALOG = my_datalog;
}


void Interpreter::createRelations(){
    vector<Predicate> schemes = MY_DATALOG.getSchemes();
    for(unsigned int i = 0; i < schemes.size(); i++){
        Relation r(schemes[i].getID());
        vector<Parameter> params = schemes[i].getParameters();
        Scheme s;
        for (unsigned int j = 0; j < params.size(); j++){
            s.push_back(params[j].getValue());
        }
        r.rename(s);
        MY_DATABASE.populateDatabase(schemes[i].getID(), r);
    }
}

void Interpreter::populateRelations(){
    vector<Predicate> facts = MY_DATALOG.getFacts();
    for (unsigned int i = 0; i < facts.size(); i++){
        vector<Parameter> params = facts[i].getParameters();
        Tuple t;
        for (unsigned int j = 0; j < params.size(); j++){
            t.push_back(params[j].getValue());
        }
        MY_DATABASE.addTuples(facts[i].getID(),t);
    }
}

void Interpreter::answerQueries(){
    vector<Predicate> queries = MY_DATALOG.getQueries();
    for (unsigned int i = 0; i < queries.size(); i++){
        answerSingleQuery(queries[i]);
    }
}

void Interpreter::answerSingleQuery(Predicate pred){
    Relation r = MY_DATABASE.getRelation(pred.getID());
    Scheme s;
    set<Tuple> temp;
    bool isEmpty = false;
    vector<Parameter> params = pred.getParameters();
    map<string, int> firstVars;
    vector<int> columnsToKeep;

    for (unsigned int i = 0; i < params.size(); i++){
        if (params[i].getType() == MY_STRING){
            r = r.select(params[i].getValue(),i);
        }
        else{
            if(firstVars.find(params[i].getValue()) != firstVars.end()){ //If Variable not already in the map
                r = r.select(firstVars[params[i].getValue()], i);
            }
            else{
                firstVars[params[i].getValue()] = i;
                columnsToKeep.push_back(i);
                s.push_back(params[i].getValue());
            }
        }
    }
    temp = r.getData();
    if (temp.size() == 0){
        isEmpty = true;
    }
    else{
        isEmpty = false;
    }
    r = r.project(columnsToKeep);
    r.rename(s);
    r.outputQuery(isEmpty, pred);
}
