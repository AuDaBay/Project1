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
Relation Relation::join(Relation relToJoin)
{
    Relation newRelation1 = newRelation();
    vector<int> tupleIndexes;

    for(unsigned int i = 0; i < relToJoin.header.attributes.size(); i++)
    {
        bool isThere = false;
        for(unsigned int j = 0; j < newRelation1.header.attributes.size(); j++)
        {
            if(!isThere)
            {
                if(newRelation1.header.attributes.at(j) == relToJoin.header.attributes.at(i))
                {
                    isThere = true;
                }
                else
                {
                    isThere = false;
                }
            }
        }
        if(!isThere)
        {
            newRelation1.header.addColumn(relToJoin.header.attributes.at(i));
            tupleIndexes.push_back(i);
        }
    }
    for(auto t: tuples)
    {
        for(auto r: relToJoin.tuples)
        {
            if(isJoinable(t, r, header, relToJoin.header))
            {
                Tuple joinedTuple = t;
                for(unsigned int k = 0; k < tupleIndexes.size(); k++)
                {
                    joinedTuple.values.push_back(r.values.at(tupleIndexes.at(k)));
                }
                newRelation1.addTuple(joinedTuple);
            }
        }
    }
    return newRelation1;
}
bool Relation::isJoinable(Tuple ogTuple, Tuple tupleToAdd, Header ogHeader, Header headerToAdd)
{
    for(unsigned int i = 0; i < ogHeader.attributes.size(); i++)
    {
        for(unsigned int j = 0; j < headerToAdd.attributes.size(); j++)
        {
            if(ogHeader.attributes.at(i) == headerToAdd.attributes.at(j))
            {
                if(ogTuple.values.at(i) != tupleToAdd.values.at(j))
                {
                    return false;
                }
            }
        }
    }
    return true;
}
bool Relation::joinToDatabase(Relation newRelation)
{
    bool shouldContinue = false;
    for(auto t: newRelation.tuples)
    {
        if(tuples.insert(t).second)
        {
            shouldContinue = true;

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
            }
            if(header.attributes.size() != 0)
            {
                cout << endl;
            }
        }
    }
    return shouldContinue;
}
int Relation::getTupleSize() {return tuples.size();}