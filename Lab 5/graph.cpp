#include "graph.h"

Graph::Graph(){}

void Graph::reverseGraph(){
    vector<Node> reverseNodeList;
    for(unsigned int i = 0; i < nodeList.size(); i++){
        reverseNodeList.push_back(Node());
    }
    for(unsigned int i = 0; i < nodeList.size(); i++){
        set<int> adjNodes = nodeList[i].getAdjNodes();
        for(set<int>::iterator it = adjNodes.begin(); it != adjNodes.end(); ++it){
            reverseNodeList[(*it)].addAdjacentNodes(i);
        }
    }
    nodeList = reverseNodeList;
}

void Graph::print(){
    for(unsigned int i = 0; i < nodeList.size(); i++){
        set<int> adjNodes = nodeList[i].getAdjNodes();
        cout << "R" << i << ":";
        int counter = 0;
        for(set<int>::iterator it = adjNodes.begin(); it != adjNodes.end(); ++it){
            counter++;
            cout << "R" << (*it);
            if((int)counter < (int)adjNodes.size()){
                cout << ",";
            }
        }
        cout << endl;
    }
}
