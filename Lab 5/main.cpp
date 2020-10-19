#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

#include <cctype>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){

    string file_name = argv[1];
    Scanner my_scanner(file_name);
    my_scanner.scan(file_name);
    vector<Token> out = my_scanner.getTokens();
    Parser my_parser(out);
    my_parser.parse();
    Datalog my_datalog = my_parser.returnDatalog();
    Interpreter my_interpreter(my_datalog);
    my_interpreter.createRelations();
    my_interpreter.populateRelations();
    my_interpreter.answerRules();
    cout << endl << "Query Evaluation" << endl;
    my_interpreter.evaluatingQueries();
    my_interpreter.answerQueries();

    return 0;
}
