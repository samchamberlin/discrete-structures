#include "node.h"

Node::Node(){
    visited = false;
    selfDependant = false;
}

void Node::addAdjacentNodes(int adjNode){
    AdjacentNodes.insert(adjNode);
}

set<int> Node::getAdjNodes(){
    return AdjacentNodes;
}

bool Node::isVisited(){
    return visited;
}

void Node::setVisited(){
    visited = true;
}

bool Node::isSelfDependant(){
    return selfDependant;
}

void Node::setSelfDependant(){
    selfDependant = true;
}
