#ifndef inputReader_h
#define inputReader_h

#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <ctype.h>
#include <locale>

using namespace std;

class inputReader{

private:

    int lineNum;
    ifstream in;

public:

    inputReader();
    inputReader(string file_name);
    ~inputReader();
    char getNextChar();
    char peekNextChar();
    bool atEOF();
    int getLineNum();
    void openFile(string file_name);

};

#endif
