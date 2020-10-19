#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Graph{

public:

    vector<Node> nodeList;
    void reverseGraph();
    void print();
    Graph();

};

#endif
