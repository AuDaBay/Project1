#include "Relation.h"
#include <iostream>
using namespace std;

Relation::Relation(Predicate scheme)
{
    name = scheme.getID();
    for(unsigned int i = 0; i < scheme.parameters.size(); i++)
    {
        header.addColumn(scheme.parameters[i].getVal());
    }
}
Relation::Relation(string title, Header head)
{
    name = title;
    header = head;

}
Relation Relation::newRelation()
{
    string tempName = name;
    Header tempHead = header;
    Relation relation = Relation(tempName, tempHead);

    return relation;
}
void Relation::addTuple(Tuple tuple)
{


    tuples.insert(tuple);

}
Relation Relation::select(int index, string value)
{

    Relation newRelation1 = newRelation();

    for(auto i: tuples)
    {
        if(i.values.at(index) == value)
        {
            newRelation1.addTuple(i);
        }
    }

    return newRelation1;
}
Relation Relation::select(int index, int index2)
{

    Relation newRelation1 = newRelation();

    for(auto i: tuples)
    {
        if(i.values.at(index) == i.values.at(index2))
        {
            newRelation1.addTuple(i);
        }
    }

    return newRelation1;
}
Relation Relation::project(vector<int> indices)
{
    Relation newRelation1 = newRelation();
    //cout << "index size = " << indices.size() << endl;
    for(auto i: tuples)
    {
        Tuple tempTuple;
        for(unsigned int j = 0; j < indices.size(); j++)
        {
            tempTuple.values.push_back(i.values.at(indices.at(j)));
        }
        newRelation1.addTuple(tempTuple);
    }
    Header tempHeader;
    for(unsigned int i = 0; i < indices.size(); i++)
    {
        tempHeader.attributes.push_back(header.attributes.at(indices.at(i)));
    }
    newRelation1.header = tempHeader;

    return newRelation1;
}
Relation Relation::rename(vector<string> attrib)
{
    Relation newRelation1 = newRelation();
    Header tempHeader;
    //cout << "new attributes size = " << attrib.size() << endl;
    for(unsigned int i = 0; i < attrib.size(); i++)
    {
        tempHeader.addColumn(attrib.at(i));
    }
    newRelation1.header = tempHeader;
    for(auto j: tuples)
    {
        newRelation1.addTuple(j);
    }

    return newRelation1;
}
void Relation::toString()
{
    for (auto t : tuples)
    {
        if(header.attributes.size() != 0)
        {
            cout << "  ";
        }
        for(unsigned int i = 0; i < header.attributes.size(); i++)
        {
            cout << header.attributes.at(i) << "=" << t.values.at(i);
            if(i < header.attributes.size() - 1)
            {
                cout << ", ";
            }
            if(i >= header.attributes.size() - 1)
            {
                cout << endl;
            }
        }
        //cout << endl;
    }

}

int Relation::getTupleSize() {return tuples.size();}