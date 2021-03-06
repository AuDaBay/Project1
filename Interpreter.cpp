#include "Interpreter.h"
using namespace std;

Interpreter:: Interpreter(Datalog dataL)
{
    datalog = dataL;
    SchemeIntoDataB(dataL.getSchemes());
    FactsIntoDataB(dataL.getFacts());
    ruleOptimization(dataL.getRules());
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
        if(currParam.isConstant)
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
            if(!isThere)
            {
                //cout << "New Variable!" << endl;
                variables.push_back(currParam.getVal());
                indexes.push_back(i);
            }
        }
    }

    Relation evaluatedQuery = currRelation.project(indexes);
    currRelation = evaluatedQuery.rename(variables);
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
void Interpreter::evaluateRules(vector<Rule> Rules, bool multiple)
{
    bool hasTuples = true;
    int numPasses = 0;
    while(hasTuples)
    {
        hasTuples = false;
        numPasses += 1;
        vector<bool> isThereMore;
        for(unsigned int i = 0; i < Rules.size(); i++)
        {
            cout << Rules.at(i).toString() << "." << endl;
            vector<Relation> ruleRelations;
            for (unsigned int j = 0; j < Rules.at(i).bodyPredicates.size(); j++)
            {
                Relation newRelation = evaluatePredicate(Rules.at(i).bodyPredicates.at(j));
                ruleRelations.push_back(newRelation);
            }
            //Join them
            Relation joinedRelation = ruleRelations.at(0);
            if (ruleRelations.size() > 1)
            {
                for (unsigned int k = 0; k < ruleRelations.size() - 1; k++)
                {
                    joinedRelation = joinedRelation.join(ruleRelations.at(k+1));
                }
            }
            //project them
            vector<int> indexes;
            for (unsigned int a = 0; a < Rules.at(i).headPredicate.parameters.size(); a++)
            {
                for (unsigned int b = 0; b < joinedRelation.header.attributes.size(); b++)//this correct?
                {
                    if (Rules.at(i).headPredicate.parameters.at(a).getVal() == joinedRelation.header.attributes.at(b))
                    {
                        indexes.push_back(b);
                    }
                }
            }
            joinedRelation = joinedRelation.project(indexes);
            //rename it to match relation
            joinedRelation.name = Rules.at(i).headPredicate.getID();

            if (dataBase.database.at(joinedRelation.name).header.attributes.size() ==
                joinedRelation.header.attributes.size())
            {
                for (unsigned int h = 0; h < joinedRelation.header.attributes.size(); h++)
                {
                    joinedRelation.header.attributes.at(h) = dataBase.database.at(
                            joinedRelation.name).header.attributes.at(h);
                }
            }
            //Union with database

            isThereMore.push_back(dataBase.database.at(joinedRelation.name).joinToDatabase(joinedRelation));
        }
        for(unsigned int j = 0; j < isThereMore.size(); j++)
        {
            if(isThereMore.at(j))
            {
                hasTuples = true;
            }
        }
         if(!multiple)
         {
          hasTuples = false;
         }

    }
    cout << numPasses << " passes: ";
}
void Interpreter::ruleOptimization(vector<Rule> Rules)
{
    Graph Forward;
    Graph Backward;
    //populate the graphs
    for(unsigned int i = 0; i < Rules.size(); i++)
    {
        Node newNode;
        newNode.ID = i;
        newNode.selfDependent = false;
        Forward.nodeList.insert({i, newNode});
        Backward.nodeList.insert({i,newNode});
    }
    for(unsigned int j = 0; j < Rules.size(); j++)
    {
        for(unsigned int k = 0; k < Rules.at(j).bodyPredicates.size(); k++)
        {
            for(unsigned int l = 0; l < Rules.size(); l++)
            {
                if(Rules.at(j).bodyPredicates.at(k).getID() == Rules.at(l).headPredicate.getID())
                {
                    bool dependentt = false;
                    if(j == l)
                    {
                        dependentt = true;
                    }
                    if(Forward.nodeList.at(j).selfDependent)
                    {
                        dependentt = true;
                    }
                    Forward.addEdge((int) j,(int) l,dependentt);
                    Backward.addEdge((int) l,(int) j,dependentt);
                }
            }
        }
    }

    Forward.toString();
    Backward.dfsForest();
    Forward.post_order = Backward.post_order;
    Forward.dfsForestForward();
    //cout << "SCC size: " << Forward.scc.size() << endl;
    cout << "Rule Evaluation" << endl;
    for(unsigned int i = 0; i < Forward.SCC.size(); i++)
    {
        vector<Rule> chosenRules;
        string outString;
        bool multi;
        unsigned int j = 0;
        //bool trivial;

        for(auto k: Forward.SCC.at(i))
        {
            chosenRules.push_back(Rules.at(k));
            string x = to_string(k);
            outString += "R" + x;
            if(Forward.SCC.at(i).size() - 1 != j)
            {
                outString += ",";
            }
            j++;
            multi = Forward.nodeList.at(k).selfDependent;
        }
        if(Forward.SCC.at(i).size() != 1)
        {
            multi = true;
        }

        cout << "SCC: " << outString << endl;
        evaluateRules(chosenRules, multi);
        cout << outString << endl;
    }
    cout << endl;
}
void Interpreter::EvaluateQueries(vector<Predicate> Queries)
{
    cout << "Query Evaluation" << endl;
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


