#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include "inputReader.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class Scanner{

private:

    inputReader in;
    int lineNum;
    vector<Token> my_tokens;

public:

    Scanner(string file_name);
    void scan(string file_name);
    void IDChecker(char c);
    bool keywordChecker(string possibleID);
    void colonMachine();
    void commentChecker();
    void blockCommentMachine();
    void commentMachine();
    void stringChecker();
    vector<Token> getTokens();
    bool isEven(int n);

};

#endif
