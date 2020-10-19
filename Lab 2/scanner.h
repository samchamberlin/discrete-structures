#ifndef scanner_h
#define scanner_h

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

/*
 Goal is to have a vector of tokens by the end of the program.

 vector<token>

 IDChecker(){

    string possibleID;

    while(isLetterDigit){

    }

}

checkForKeyword(possibleID)
{
    if (possibleID == "schemes")
}

 function scan(){
    while(! in.atEOF){
        char my_char
        my_char = in.getNextChar;
        switch(my_char)

        case: ','{
            make comma token
        }

        case: ':'{
            colonMachine();
        }

        **etc. for every single TOKEN TYPE**

        default
        if(in.isLetter()){
            IDChecker();
        }
        else
            undefined;
    }
 }

 colonMachine(){
    if (in.peek == '-')
        colonDash();
    else
        colon;
 }

 EXAMPLE
    '.Hello'n
    World!


 */

#endif
