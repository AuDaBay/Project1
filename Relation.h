#ifndef PROJECT1_RELATION_H
#define PROJECT1_RELATION_H
#include <string>
#include <set>
#include "Tuple.h"
#include "Header.h"
#include "Predicate.h"
using namespace std;


class Relation {
public:
    Relation(string title, Header head);
    Relation(Predicate Scheme);
    Relation newRelation();
    void addTuple(Tuple tuple);
    void toString();
    int getTupleSize();
    Relation select(int index, string value);
    Relation select(int index, int index2);
    Relation project(vector<int> indices);
    Relation rename(vector<string> attributes);

private:
    set<Tuple> tuples;
    string name;
    Header header;

};


#endif //PROJECT1_RELATION_H
