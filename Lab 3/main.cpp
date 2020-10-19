#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

#include <cctype>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){

    string file_name = argv[1]; //read in from commandline
    Scanner my_scanner(file_name); //give file to scanner
    my_scanner.scan(file_name);
    vector<Token> out = my_scanner.getTokens();
    Parser my_parser(out);
    my_parser.parse();
    Datalog my_datalog = my_parser.returnDatalog();
    Interpreter my_interpreter(my_datalog);
    my_interpreter.createRelations();
    my_interpreter.populateRelations();
    my_interpreter.answerQueries();

    return 0;
}





























































/*



*/
