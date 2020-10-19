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
    if(temp.size() == 0){
        isEmpty = true;
    }
    else{
        isEmpty = false;
    }
    r = r.project(columnsToKeep);
    r.rename(s);
    if(evaluateQueries){
        r.outputQuery(isEmpty, pred);
    }
    return r;
}

void Interpreter::answerRules(){
    vector<Rule> rules = MY_DATALOG.getRules();
    buildGraphs();
    MY_GRAPH.print();
    MY_REVERSE_GRAPH = MY_GRAPH;
    MY_REVERSE_GRAPH.reverseGraph();
    dfsForest();
    vector<set<int>> mySCC;
    dfsForestSCC();
    cout << endl << "Rule Evaluation" << endl;
    for(unsigned int i = 0; i < SCC.size(); i++){
        bool allowed = false;
        for(set<int>::iterator it = SCC[i].begin(); it != SCC[i].end(); it++){
            if (SCC[i].size() == 1 && !MY_GRAPH.nodeList[*it].isSelfDependant()){
                cout << "SCC: R" << (*it) << endl;
                evaluateSingleRule(rules[*it]);
                cout << "1 passes: R" << (*it) << endl;
            }
            else{
                allowed = true;
            }
        }
        if (allowed == true){
            printSCC(SCC[i]);
            fixedPoint(SCC[i], i);
        }
    }
}

void Interpreter::printSCC(set<int> mySCC){
    int counter = 0;
    cout << "SCC: ";
    for(set<int>::iterator it = mySCC.begin(); it != mySCC.end(); it++){
        counter++;
        cout << "R" << *it;
        if((int)counter < (int)mySCC.size()){
            cout << ",";
        }
    }
    cout << endl;
}

void Interpreter::fixedPoint(set<int> mySCC, int i){
    int numTimesRepeated = 0;
    int numTuplesBefore = 0;
    int numTuplesAfter = 0;
    while(true){
        numTuplesBefore = MY_DATABASE.getNumTuples();
        for(set<int>::iterator it = SCC[i].begin(); it != SCC[i].end(); it++){
            evaluateSingleRule(MY_DATALOG.getRules()[*it]);
        }
        numTimesRepeated++;
        numTuplesAfter = MY_DATABASE.getNumTuples();
        if(numTuplesAfter == numTuplesBefore){
            break;
        }
    }
    int counter = 0;
    cout << numTimesRepeated << " passes: ";
    for(set<int>::iterator it = SCC[i].begin(); it != SCC[i].end(); it++){
        counter++;
        cout << "R" << *it;
        if((int)counter < (int)mySCC.size()){
            cout << ",";
        }
    }
    cout << endl;
}

void Interpreter::evaluateSingleRule(Rule rule){
    Predicate headPred = rule.getHeadPredicate();
    vector<Predicate> predList = rule.getPredicateList();
    vector<Relation> relList;
    set<Tuple> databaseData;
    string headName = headPred.getID();
    for(unsigned int i = 0; i < predList.size(); i++){
        Relation tempRelation;
        tempRelation = answerSingleQuery(predList[i]);
        relList.push_back(tempRelation);
    }
    Relation newRelation = relList[0];
    for(unsigned int j = 1; j < relList.size(); j++){
        Relation tempRelation = relList[j];
        newRelation = newRelation.join(tempRelation);
    }
    vector<int> columnsInOrder;
    vector<Parameter> headParams = headPred.getParameters();
    Scheme newRelScheme = newRelation.getHeaders();
    for(unsigned int l = 0; l < headParams.size(); l++){
        for(unsigned int n = 0; n < newRelScheme.size(); n++){
            if(headParams[l].getValue() == newRelScheme[n]){
                columnsInOrder.push_back(n);
            }
        }
    }
    Relation finalRelation = newRelation.project(columnsInOrder);
    cout << rule.toString() << endl;
    Relation& databaseRelation = MY_DATABASE.getRelationReference(headName);
    databaseRelation.unionAdd(finalRelation);
}

void Interpreter::buildGraphs(){
    vector<Rule> rules = MY_DATALOG.getRules();
    Predicate headPred;
    Predicate pred;
    vector<Predicate> predList;
    string predName;
    string headName;
    Relation r;
    Relation databaseRelation;
    set<Tuple> databaseData;
    cout << "Dependency Graph" << endl;
    for(unsigned int i = 0; i < rules.size(); i++){
        MY_GRAPH.nodeList.push_back(Node());
        predList = rules[i].getPredicateList();
        for(unsigned int j = 0; j < predList.size(); j++){
            pred = predList[j];
            predName = pred.getID();
            for(unsigned int k = 0; k < rules.size(); k++){
                headPred = rules[k].getHeadPredicate();
                headName = headPred.getID();
                if (headName == predName){
                    MY_GRAPH.nodeList[i].addAdjacentNodes(k);
                }
            }
        }
    }
    for(unsigned int i = 0; i < MY_GRAPH.nodeList.size(); i++){
        set<int> adjNodes = MY_GRAPH.nodeList[i].getAdjNodes();
        for(set<int>::iterator it = adjNodes.begin(); it != adjNodes.end(); ++it){
            if(*it == (int)i){
                MY_GRAPH.nodeList[i].setSelfDependant();
            }
        }
    }
}

void Interpreter::dfsForest(){
    for(unsigned int i = 0; i < MY_REVERSE_GRAPH.nodeList.size(); i++){
        if(!MY_REVERSE_GRAPH.nodeList[i].isVisited()){
            dfs(MY_REVERSE_GRAPH.nodeList[i], i);
        }
    }
}

void Interpreter::dfs(Node& node, int index){
    node.setVisited();
    set<int> adjNodes = node.getAdjNodes();
    for(set<int>::iterator it = adjNodes.begin(); it != adjNodes.end(); ++it){
        if(!MY_REVERSE_GRAPH.nodeList[(*it)].isVisited()){
            dfs(MY_REVERSE_GRAPH.nodeList[(*it)], *it);
        }
    }
    nodeStack.push(index);
}

void Interpreter::dfsForestSCC(){
    set<int> mySCCset;
    while(!nodeStack.empty()){
        int i = nodeStack.top();
        if(!MY_GRAPH.nodeList[i].isVisited()){
            mySCCset = dfsSCC(MY_GRAPH.nodeList[i], i);
            SCC.push_back(mySCCset);
        }
        nodeStack.pop();
    }
}

set<int> Interpreter::dfsSCC(Node& node, int index){
    set<int> mySCCset;
    set<int> returningSCCset;
    set<int> adjNodes = node.getAdjNodes();
    node.setVisited();
    mySCCset.insert(index);
    for(set<int>::iterator it = adjNodes.begin(); it != adjNodes.end(); ++it){
        if(!MY_GRAPH.nodeList[(*it)].isVisited()){
            returningSCCset = dfsSCC(MY_GRAPH.nodeList[(*it)], *it);
            for(set<int>::iterator it2 = returningSCCset.begin(); it2 != returningSCCset.end(); it2++){
                mySCCset.insert(*it2);
            }

        }
    }
    return mySCCset;
}
