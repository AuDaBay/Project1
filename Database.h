#ifndef PROJECT1_DATABASE_H
#define PROJECT1_DATABASE_H
#include <map>
#include "Relation.h"
using namespace std;

class Database {
public:
    map<string, Relation> database;
    void addRelation(string name, Relation relation);
    void addTupleToRelation(string name, Tuple tuple);
    void toString();
    //Relation& getRelation(string str);
};


#endif //PROJECT1_DATABASE_H
