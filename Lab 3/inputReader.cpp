#include "inputReader.h"

inputReader::inputReader(){}

inputReader::inputReader(string file_name){
   string file = file_name;
   lineNum = 1;
}

inputReader::~inputReader(){}

void inputReader::openFile(string file_name){
   in.open(file_name);
}

char inputReader::getNextChar(){
   char c = in.get();
   if(c == '\n'){
      lineNum++;
   }
   return c;
}

char inputReader::peekNextChar(){
   char c = in.peek();
   return c;
}

bool inputReader::atEOF(){
   if (in.eof()){
       return true;
   }
   else
       return false;
}

int inputReader::getLineNum(){
   return lineNum;
}
