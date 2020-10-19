#include "database.h"

void Database::populateDatabase(string name, Relation relation){
    relations[name] = relation;
}

void Database::addTuples(string name, Tuple tuple){
    relations[name].addTuple(tuple);
}

Relation Database::getRelation(string name){
    Relation r = relations[name];
    return r;
}

Relation& Database::getRelationReference(string name){
    return relations[name];
}

void Database::printAllRelations(){
    cout << "Here's your database: " << endl;
    for(map<string, Relation>::iterator it = relations.begin(); it != relations.end(); ++it){
        (*it).second.outputRelation();
    }
    cout << endl;
}

int Database::getNumTuples(){
    int numTuples = 0;
    for(map<string, Relation>::iterator it = relations.begin(); it != relations.end(); ++it){
        numTuples += (*it).second.getData().size();
    }
    return numTuples;
}
