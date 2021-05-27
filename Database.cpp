#include "Database.h"
#include <iostream>
using namespace std;

void Database::addRelation(string name, Relation relation)
{
    database.insert({name, relation});
}
void Database::addTupleToRelation(string name, Tuple tuple)
{
    database.at(name).addTuple(tuple);
}
void Database::toString()
{
    string str;
    for(auto i: database)
    {
        i.second.toString();
    }
}

//Relation& Database::getRelation(string str)
//{
//    return database.at(str);
//}