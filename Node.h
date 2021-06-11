#ifndef PROJECT1_NODE_H
#define PROJECT1_NODE_H
#include <set>
using namespace std;

class Node {
public:
    set<int> adjacents;
    int ID;
    bool visited;
    bool selfDependent;
    Node() {visited = false;}
};


#endif //PROJECT1_NODE_H
