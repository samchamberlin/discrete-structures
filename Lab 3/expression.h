#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <ctype.h>
#include <locale>
#include "token.h"
#include "parameter.h"

class Expression: public Parameter {

    Parameter* left;
    string op;
    Parameter* right;

};

#endif
