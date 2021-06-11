#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H
#include <map>
#include "Node.h"
#include <stack>
#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
    map<int, Node> nodeList;
    stack<int> post_order;
    vector<set<int>> SCC;
    set<int> local;
    void dfs(Node thisNode);
    void dfsForest();
    void dfsForestForward();
    void dfsSCC(Node thisNode);
    void addEdge(int source, int to, bool dependent);
    void toString();
};
#endif //PROJECT1_GRAPH_H
