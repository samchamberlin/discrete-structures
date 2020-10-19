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
