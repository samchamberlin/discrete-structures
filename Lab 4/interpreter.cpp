#include "interpreter.h"

Interpreter::Interpreter(Datalog my_datalog){
    MY_DATALOG = my_datalog;
    evaluateQueries = false;
}

void Interpreter::evaluatingQueries(){
    evaluateQueries = true;
}


void Interpreter::createRelations(){
    vector<Predicate> schemes = MY_DATALOG.getSchemes();
    for(unsigned int i = 0; i < schemes.size(); i++){
        Relation r(schemes[i].getID());
        vector<Parameter> params = schemes[i].getParameters();
        Scheme s;
        for(unsigned int j = 0; j < params.size(); j++){
            s.push_back(params[j].getValue());
        }
        r.rename(s);
        MY_DATABASE.populateDatabase(schemes[i].getID(), r);
    }
}

void Interpreter::populateRelations(){
    vector<Predicate> facts = MY_DATALOG.getFacts();
    for(unsigned int i = 0; i < facts.size(); i++){
        vector<Parameter> params = facts[i].getParameters();
        Tuple t;
        for(unsigned int j = 0; j < params.size(); j++){
            t.push_back(params[j].getValue());
        }
        MY_DATABASE.addTuples(facts[i].getID(),t);
    }
}

void Interpreter::answerQueries(){
    vector<Predicate> queries = MY_DATALOG.getQueries();
    for(unsigned int i = 0; i < queries.size(); i++){
        answerSingleQuery(queries[i]);
    }
}

Relation Interpreter::answerSingleQuery(Predicate pred){
    Relation r = MY_DATABASE.getRelation(pred.getID());
    Scheme s;
    set<Tuple> temp;
    bool isEmpty = false;
    vector<Parameter> params = pred.getParameters();
    map<string, int> firstVars;
    vector<int> columnsToKeep;
    for(unsigned int i = 0; i < params.size(); i++){
        if(params[i].getType() == MY_STRING){
            r = r.select(params[i].getValue(),i);
        }
        else{
            if(firstVars.find(params[i].getValue()) != firstVars.end()){
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
    if (evaluateQueries){
        r.outputQuery(isEmpty, pred);
    }
    return r;
}

int Interpreter::answerRules(){
    vector<Rule> rules = MY_DATALOG.getRules();
    Predicate headPred;
    Relation r;
    Relation databaseRelation;
    set<Tuple> databaseData;
    string headName = headPred.getID();
    int numTuplesBefore = 0;
    int numTuplesAfter = 0;
    int numTimesRepeated = 0;
    while(true){
        numTuplesBefore = MY_DATABASE.getNumTuples();
        evaluateRules();
        numTimesRepeated++;
        numTuplesAfter = MY_DATABASE.getNumTuples();
        if (numTuplesAfter == numTuplesBefore){
            break;
        }
    }
    return numTimesRepeated;
}

void Interpreter::evaluateRules(){
    vector<Rule> rules = MY_DATALOG.getRules();
    for(unsigned int i = 0; i < rules.size(); i++){
        evaluateSingleRule(rules[i]);
    }
}

void Interpreter::evaluateSingleRule(Rule rule){
    Predicate headPred = rule.getHeadPredicate();
    vector<Predicate> predList = rule.getPredicateList();
    vector<Relation> relList;
    set<Tuple> databaseData;
    string headName = headPred.getID();
    for (unsigned int i = 0; i < predList.size(); i++){
        Relation tempRelation;
        tempRelation = answerSingleQuery(predList[i]);
        relList.push_back(tempRelation);
    }
    Relation newRelation = relList[0];
    for (unsigned int j = 1; j < relList.size(); j++){
        Relation tempRelation = relList[j];
        newRelation = newRelation.join(tempRelation);
    }
    vector<int> columnsInOrder;
    vector<Parameter> headParams = headPred.getParameters();
    Scheme newRelScheme = newRelation.getHeaders();
    for (unsigned int l = 0; l < headParams.size(); l++){
        for (unsigned int n = 0; n < newRelScheme.size(); n++){
            if (headParams[l].getValue() == newRelScheme[n]){
                columnsInOrder.push_back(n);
            }
        }
    }
    Relation finalRelation = newRelation.project(columnsInOrder);
    cout << rule.toString() << endl;
    Relation& databaseRelation = MY_DATABASE.getRelationReference(headName);
    databaseRelation.unionAdd(finalRelation);
}
