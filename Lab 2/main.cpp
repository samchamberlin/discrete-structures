#include "scanner.h"
#include "token.h"
#include "parser.h"

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

    //Print Tokens to screen
/*
    vector<Token> tokenVector = my_scanner.getTokens();

    for(unsigned int i = 0; i < tokenVector.size(); i++){

        cout << tokenVector[i].toString();
    }

    cout << "Total Tokens = " << tokenVector.size() << endl;
*/

    //Lab 2 Output

    return 0;
}
