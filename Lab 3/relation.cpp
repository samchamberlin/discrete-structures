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
    for (set<Tuple>::iterator it = DATA.begin(); it != DATA.end(); ++it){
        if((*it)[col] == val){
            result.addTuple(*it);
        }
    }
    return result;
}

Relation Relation::select(int column1, int column2){
    Relation result = Relation(NAME, HEADERS);
    for (set<Tuple>::iterator it = DATA.begin(); it != DATA.end(); ++it){
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
    for (set<Tuple>::iterator it = DATA.begin(); it != DATA.end(); ++it){
        Tuple newTuple;
        for (unsigned int k = 0; k < columnsToKeep.size(); k++){
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
    if(isEmpty){
        cout << "No" << endl;
    }
    else{
        cout << "Yes(" << DATA.size() << ")" << endl;
    }
    if(HEADERS.size() != 0){
        for (set<Tuple>::iterator it = DATA.begin(); it != DATA.end(); ++it){
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
