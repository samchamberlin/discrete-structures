//File: Project 1 - CS 236
//Author: Sam Chamberlin
//Date: January 22, 2019
//This program is a scanner

#include "scanner.h"
#include "token.h"

#include <cctype>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){

    string file_name = argv[1];
    Scanner my_scanner(file_name);
    my_scanner.scan(file_name);

    //Print Tokens to screen
    vector<Token> tokenVector = my_scanner.getTokens();
    for(unsigned int i = 0; i < tokenVector.size(); i++){
        cout << tokenVector[i].toString();
    }
    cout << "Total Tokens = " << tokenVector.size() << endl;

    return 0;
}





























































/*



*/
