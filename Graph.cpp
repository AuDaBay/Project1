#include "Graph.h"

void Graph::dfsForest()
{
    for(auto i: nodeList)
    {
        if(!i.second.visited)
        {
            dfs(i.second);
        }
    }
}

void Graph::dfs(Node thisNode)
{
    if(!thisNode.visited)
    {
        //cout << "in dfs" << endl;
        nodeList.at(thisNode.ID).visited = true;
        for(auto i: thisNode.adjacents)
        {
            if(nodeList[i].visited == false)
            {
                dfs(nodeList[i]);
            }
        }

        post_order.push(thisNode.ID);
    }
    else
    {
        return;
    }
}
void Graph::addEdge(int source, int to, bool dependent)
{
    nodeList.at(source).adjacents.insert(to);
    nodeList.at(source).selfDependent = dependent;
}
void Graph::dfsSCC(Node thisNode)
{
    //cout << "Searching for Node " << thisNode.ID << endl;
    if(!thisNode.visited)
    {
        //cout << "in dfsSCC"<< endl;
        //cout << "current Node " << nodeList.at(thisNode.ID).ID;
        nodeList.at(thisNode.ID).visited = true;
        //cout << "has been visited" << nodeList.at(thisNode.ID).visited << endl;
        local.insert(thisNode.ID);
        //cout << thisNode.ID << "has an adjaceny list size " << thisNode.adjacents.size() << endl;
        for(auto i: thisNode.adjacents)
        {
            //cout << "adjacent visited" << nodeList.at(i).visited << endl;
            if(nodeList.at(i).visited == false)
            {
                //cout << "searching for adjacents!" << endl;
                dfsSCC(nodeList.at(i));
            }
        }
    }
    else
    {
        //cout << "We have visited this one!" << endl;
    }
}
void Graph::dfsForestForward()
{

    while(!post_order.empty())
    {
//        cout << "post order size: " << post_order.size() << endl;
//        cout << "current node visited" << nodeList[post_order.top()].visited << endl;
//        cout << "in dfsForestForward" << endl;
        //cout << nodeList.at(post_order.top()).ID;
        if(!nodeList[post_order.top()].visited)
        {
            dfsSCC(nodeList[post_order.top()]);
        }
        else
        {
            //cout << "in else";
            if(local.size() != 0)
            {
                //cout << "adding SCC" << endl;
                SCC.push_back(local);
                local.clear();
            }
            post_order.pop();
        }

        //cout << nodeList.at(post_order.top()).ID << "visited: " << nodeList[post_order.top()].visited << endl;
    }
}
void Graph::toString()
{
    cout << "Dependency Graph" << endl;
    for(auto i: nodeList)
    {
        cout << "R" << i.first << ":";
        int adjacencies = i.second.adjacents.size();
        //cout << adjacencies;
        int x = 0;
        for( auto j: i.second.adjacents)
        {
            if(x != adjacencies - 1)
            {
                cout << "R" << j << ",";
            }
            else
            {
                cout << "R" << j;
            }
            x++;
        }
        cout << endl;
    }
    cout << endl;
}
