#ifndef NODE_H
#define NODE_H

#include <set>
#include <iostream>

using namespace std;

class Node{

private:

    set<int> AdjacentNodes;
    bool visited;
    bool selfDependant;
    int postOrder;

public:

    void addAdjacentNodes(int adjNode);
    set<int> getAdjNodes();
    bool isVisited();
    void setVisited();
    bool isSelfDependant();
    void setSelfDependant();
    Node();

};

#endif
