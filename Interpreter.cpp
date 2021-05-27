#include "Interpreter.h"
using namespace std;

Interpreter:: Interpreter(Datalog dataL)
{
    datalog = dataL;
    SchemeIntoDataB(dataL.getSchemes());
    FactsIntoDataB(dataL.getFacts());
    EvaluateQueries(dataL.getQueries());



}
Relation Interpreter::evaluatePredicate(Predicate query)
{
    string relName = query.getID();
    vector<int> indexes;
    vector<string> variables;
    Relation currRelation = dataBase.database.at(relName);

    for(unsigned int i = 0; i < query.parameters.size(); i++)
    {
        Parameter currParam = query.parameters.at(i);
        //cout << "Current val being evaluated: " << currParam.getVal() << endl;
        if(currParam.isConstant == true)
        {
            //cout << "Constant is: " << currParam.getVal() << endl;
            string val = currParam.getVal();
            currRelation = currRelation.select(i,val);
        }
        else
        {

            bool isThere = false;
            for(unsigned int j = 0; j < variables.size(); j++ )
            {
                if(variables.at(j) == currParam.getVal())
                {
                    //cout << "duplicate found" << endl;
                    isThere = true;
                    currRelation = currRelation.select(i,j);
                }
            }
            if(isThere == false)
            {
                //cout << "New Variable!" << endl;
                variables.push_back(currParam.getVal());
                indexes.push_back(i);
            }
        }
    }
//    cout << "String.size() = " << variables.size() << endl;
//    cout << "Indexes.size() = " << indexes.size() << endl;
//    cout << "Before project and rename" << currRelation.getTupleSize() << endl;
    Relation evaluatedQuery = currRelation.project(indexes);
    currRelation = evaluatedQuery.rename(variables);
    //cout << "After project and rename" << currRelation.getTupleSize() << endl;
    return currRelation;
}

void Interpreter::SchemeIntoDataB(vector<Predicate> Schemes)
{
    for(unsigned int i = 0; i < Schemes.size(); i++)
    {
        string name = Schemes.at(i).getID();
        Relation newRelation(Schemes.at(i));
        dataBase.addRelation(name, newRelation);
    }
}

void Interpreter::FactsIntoDataB(vector<Predicate> Facts)
{
    for(unsigned int i = 0; i < Facts.size(); i++)
    {

        string title = Facts.at(i).getID();
        Tuple newTuple;
        for(unsigned int j = 0; j < Facts.at(i).parameters.size(); j++)
        {
            newTuple.values.push_back(Facts.at(i).parameters.at(j).getVal());

        }
        dataBase.addTupleToRelation(title, newTuple);

    }
}
void Interpreter::EvaluateQueries(vector<Predicate> Queries)
{
    for(unsigned int i = 0; i < Queries.size(); i++)
    {
        Relation evaluatedQuery = evaluatePredicate(Queries.at(i));
        cout << Queries.at(i).toString() << "? ";
        if(evaluatedQuery.getTupleSize() == 0)
        {
            cout << "No" << endl;
        }
        else
        {
            cout << "Yes(" << evaluatedQuery.getTupleSize() << ")" << endl;
            evaluatedQuery.toString();
        }
    }
}
void Interpreter::toString()
{
    dataBase.toString();
}


