#ifndef PARAMETER_H
#define PARAMETER_H

#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <ctype.h>
#include <locale>
#include "token.h"
enum ParamType{
    MY_ID, MY_STRING, MY_EXPRESSION
};

class Parameter{

public:

    Parameter();
    Parameter(ParamType type, string value);
    ~Parameter();

    ParamType TYPE; //0 = ID, 1 = string, 2 = expression
    string VALUE;
    string getValue();
    ParamType getType();
    string toString();

};

#endif
