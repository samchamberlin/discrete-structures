#include "parameter.h"

Parameter::Parameter(){}

Parameter::Parameter(ParamType type, string value){
    TYPE = type;
    VALUE = value;
}

Parameter::~Parameter(){}

string Parameter::getValue(){
        return VALUE;
}

ParamType Parameter::getType(){
        return TYPE;
}

string Parameter::toString(){
        return VALUE;
}
