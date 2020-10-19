#include "relation.h"

Relation::Relation(string name){
    NAME = name;
}

Relation::Relation(string name, Scheme headers){
    NAME = name;
    HEADERS = headers;
}

Relation::Relation(string name, Scheme headers, set<Tuple> data){
    NAME = name;
    HEADERS = headers;
    DATA = data;
}

Relation::~Relation(){}

Relation Relation::select(string val, int col){
    Relation result = Relation(NAME, HEADERS);
    for(set<Tuple>::iterator it = DATA.begin(); it != DATA.end(); ++it){
        if((*it)[col] == val){
            result.addTuple(*it);
        }
    }
    return result;
}

Relation Relation::select(int column1, int column2){
    Relation result = Relation(NAME, HEADERS);
    for(set<Tuple>::iterator it = DATA.begin(); it != DATA.end(); ++it){
        if((*it)[column1] == (*it)[column2]){
            result.addTuple(*it);
        }
    }
    return result;
}

Relation Relation::project(vector<int> columnsToKeep){
    Scheme newScheme;
    for(unsigned int i = 0; i < columnsToKeep.size(); i++){
        newScheme.push_back(HEADERS[columnsToKeep[i]]);
    }
    Relation result = Relation(NAME, newScheme);
    for(set<Tuple>::iterator it = DATA.begin(); it != DATA.end(); ++it){
        Tuple newTuple;
        for(unsigned int k = 0; k < columnsToKeep.size(); k++){
            newTuple.push_back((*it)[columnsToKeep[k]]);
        }
        result.addTuple(newTuple);
    }
    return result;
}

void Relation::rename(Scheme sch){
    HEADERS = sch;
}

void Relation::addTuple(Tuple tuple){
    DATA.insert(tuple);
}

set<Tuple> Relation::getData(){
    return DATA;
}

Scheme Relation::getHeaders(){
    return HEADERS;
}

void Relation::outputQuery(bool isEmpty, Predicate query){
    cout << query.toString() << "? ";
    if(isEmpty){ //Empty Relation unsigned
        cout << "No" << endl;
    }
    else{
        cout << "Yes(" << DATA.size() << ")" << endl;
    }
    if(HEADERS.size() != 0){
        for(set<Tuple>::iterator it = DATA.begin(); it != DATA.end(); ++it){
            cout << "  ";
            for(unsigned int i = 0; i < HEADERS.size(); i++){
                cout << HEADERS[i] << "=" << (*it)[i];
                if (i  != HEADERS.size() - 1){
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
}

void Relation::unionAdd(Relation finalRelation){
    set<Tuple> finalRelTuples = finalRelation.getData();
    for(set<Tuple>::iterator it = finalRelTuples.begin(); it != finalRelTuples.end(); ++it){
        if(DATA.count(*it) == 0){ // if Tuple in finalRelTuples (new Relation) isn't in DATA (database)
            addTuple(*it);
            cout << "  ";
            for(unsigned int i = 0; i < HEADERS.size(); i++){
                cout << HEADERS[i] << "=" << (*it)[i];
                if(i  != (HEADERS.size() - 1)){
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
}

Relation Relation::join(Relation r2){ //  r3 = r1.join(r2)
    Relation r3 = Relation(NAME);
    vector<pair<int, int>> matchingColumns;
    Scheme schemesR2 = r2.getHeaders();
    Scheme newScheme = joinSchemes(matchingColumns, schemesR2);
    r3.rename(newScheme);
    set<Tuple> tuplesR2 = r2.getData();
    for(set<Tuple>::iterator it = DATA.begin(); it != DATA.end(); ++it){
        for(set<Tuple>::iterator it2 = tuplesR2.begin(); it2 != tuplesR2.end(); ++it2){
            Tuple t1 = (*it);
            Tuple t2 = (*it2);
            if(joinable(t1, t2, matchingColumns)){
                set<int> matchingColumnsSet;
                for(unsigned int i = 0; i < matchingColumns.size(); i++){
                    matchingColumnsSet.insert(matchingColumns[i].first);
                }
                Tuple joinedTuple = joinTuples(t1, t2, matchingColumnsSet);
                r3.addTuple(joinedTuple);
            }
        }
    }
    return r3;
}

Scheme Relation::joinSchemes(vector<pair<int, int>>&matchingColumns, Scheme schemesR2){
    Scheme newScheme = HEADERS; // HEADERS = r1
    for (unsigned int j = 0; j < schemesR2.size(); j++){ //loop through r2
        for(unsigned int i = 0; i < HEADERS.size(); i++){ //loop through r1
            if (HEADERS[i] == schemesR2[j]){
                matchingColumns.push_back(make_pair(j,i));
                break;
            }
            if (i == HEADERS.size() - 1){
                newScheme.push_back(schemesR2[j]);//add to schemes
            }
        }
    }
    return newScheme;
}

Tuple Relation::joinTuples(Tuple t1, Tuple t2, set<int> matchingColumnsSet){
    Tuple joinedTuple = t1;
    for(unsigned int i = 0; i < t2.size(); i++){
        const bool is_in = matchingColumnsSet.find(i) != matchingColumnsSet.end();
        if(!is_in){
            joinedTuple.push_back(t2[i]);
        }
    }
    return joinedTuple;
}

bool Relation::joinable(Tuple t1, Tuple t2, vector<pair<int, int>> matchingColumns){
    for(unsigned int i = 0; i < matchingColumns.size(); i++){
        if(t1[matchingColumns[i].second] != t2[matchingColumns[i].first]){
            return false;
        }
    }
    return true;
}

void Relation::outputRelation(){
    if(HEADERS.size() != 0){
        for(set<Tuple>::iterator it = DATA.begin(); it != DATA.end(); ++it){
            cout << "  ";
            for(unsigned int i = 0; i < HEADERS.size(); i++){
                cout << HEADERS[i] << "=" << (*it)[i];
                if(i != HEADERS.size() - 1){
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
}
