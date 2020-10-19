#include "scanner.h"

#include <cctype>
#include <vector>
#include <cstdio>

using namespace std;

Scanner::Scanner(string file_name): in(file_name){

}

void Scanner::scan(string file_name){

    in.openFile(file_name);

    lineNum = 1;

    while(!in.atEOF()){

        char my_char = in.getNextChar();

        switch (my_char){

        case ',' :

            lineNum = in.getLineNum();

            my_tokens.push_back(Token(COMMA, ",", lineNum));

            break;

        case '.' :

            lineNum = in.getLineNum();

            my_tokens.push_back(Token(PERIOD, ".", lineNum));

            break;

        case '?' :

            lineNum = in.getLineNum();

            my_tokens.push_back(Token(Q_MARK, "?", lineNum));

            break;

        case '(' :

            lineNum = in.getLineNum();

            my_tokens.push_back(Token(LEFT_PAREN, "(", lineNum));

            break;

        case ')' :

            lineNum = in.getLineNum();

            my_tokens.push_back(Token(RIGHT_PAREN, ")", lineNum));

            break;

        case '*' :

            lineNum = in.getLineNum();

            my_tokens.push_back(Token(MULTIPLY, "*", lineNum));

            break;

        case '+' :

            lineNum = in.getLineNum();

            my_tokens.push_back(Token(ADD, "+", lineNum));

            break;

        case ':' :

            lineNum = in.getLineNum();

            colonMachine();

            break;

        case '#' :

            lineNum = in.getLineNum();

            commentChecker();

            break;

        case '\'' :

            lineNum = in.getLineNum();

            stringChecker();

            break;

        default:

            if (isalpha(my_char)){

                lineNum = in.getLineNum();

                IDChecker(my_char);
            }

            else if (isspace(my_char)){

                lineNum = in.getLineNum();

                break;
            }


            /*
            Undefined Tokens are:

            A single character that cannot be the first character of a valid Token.
            A string that is not terminated.
            A comment that is not terminated.
            */
            else{

                if (my_char != -1){

                    stringstream ss;

                    ss << my_char;

                    lineNum = in.getLineNum();

                    my_tokens.push_back(Token(UNDEFINED, ss.str(), lineNum));

                    break;
                }
                else{

                    break;
                }
            }
        }
    }

    //EOF

    lineNum = in.getLineNum();

    my_tokens.push_back(Token(MY_EOF, "", lineNum));
}

void Scanner::IDChecker(char c){

    string possibleID = "";

    possibleID += c;

    lineNum = in.getLineNum();

    while (true){

        if (keywordChecker(possibleID)){

            break;
        }

        else if (in.atEOF()){

            my_tokens.push_back(Token(ID, possibleID, lineNum));

            break;
         }

         else if (isalpha(in.peekNextChar())){

            possibleID += in.getNextChar();
         }

         else if (isalnum(in.peekNextChar())){

            possibleID += in.getNextChar();
         }

        else{

            my_tokens.push_back(Token(ID, possibleID, lineNum));

            break;
        }
    }
}

bool Scanner::keywordChecker(string possibleID){

    if(!isalpha(in.peekNextChar()) && !isalnum(in.peekNextChar())){

        if (possibleID == "Schemes"){

            lineNum = in.getLineNum();

            my_tokens.push_back(Token(SCHEMES, "Schemes", lineNum));

            return true;
        }

        else if (possibleID == "Facts"){

            lineNum = in.getLineNum();

            my_tokens.push_back(Token(FACTS, "Facts", lineNum));

            return true;

        }

        else if (possibleID == "Rules"){

            lineNum = in.getLineNum();

            my_tokens.push_back(Token(RULES, "Rules", lineNum));

            return true;
        }


        else if (possibleID == "Queries"){

            lineNum = in.getLineNum();

            my_tokens.push_back(Token(QUERIES, "Queries", lineNum));

            return true;
        }
        else{

            return false;
        }
    }

    else {

        return false;
    }

}

void Scanner::colonMachine(){

   if (in.peekNextChar() == '-'){

       lineNum = in.getLineNum();

       my_tokens.push_back(Token(COLON_DASH, ":-", lineNum));

       in.getNextChar();
   }

   else{

       lineNum = in.getLineNum();

       my_tokens.push_back(Token(COLON, ":", lineNum));
   }

}

void Scanner::commentChecker(){


    if (in.peekNextChar() == '|'){

        blockCommentMachine();
    }

    else{

        commentMachine();
    }
}


void Scanner::blockCommentMachine(){

    string str = "";

    str += '#';

    int startingLineNum = lineNum;

    char curr = ' ';

    while (true){

        if (in.peekNextChar() == EOF){

            my_tokens.push_back(Token(UNDEFINED, str, startingLineNum));

            break;
        }

        else if (in.peekNextChar() == '|'){

            curr = in.getNextChar();

            str += curr;

            if (in.peekNextChar() == '#'){

                curr = in.getNextChar();

                str += curr;

                //my_tokens.push_back(Token(COMMENT, str, startingLineNum));

                break;
            }
        }

        else{

            curr = in.getNextChar();

            str += curr;
        }

    }
}

void Scanner::commentMachine(){

    string str = "";

    str += '#';

    //int startingLineNum = lineNum;

    char curr = ' ';

    while(true){

        if (in.peekNextChar() == '\n'){

            //curr = in.getNextChar();

            //str += curr;

            //my_tokens.push_back(Token(COMMENT, str, startingLineNum));

            break;
        }

        else if (in.atEOF()){

            //my_tokens.push_back(Token(COMMENT, str, startingLineNum));

            break;
        }

        else{

            curr = in.getNextChar();

            str += curr;

            continue;
        }

    }
}

void Scanner::stringChecker(){

    string str = "";

    str += '\'';

    char curr = ' ';

    int startingLineNum = lineNum;

    while (true){

        if (in.peekNextChar() == EOF){

            my_tokens.push_back(Token(UNDEFINED, str, startingLineNum));

            break;
        }

        else if (in.peekNextChar() == '\''){

            curr = in.getNextChar();

            str += curr;

            if (in.peekNextChar() == '\''){

                curr = in.getNextChar();

                str += curr;

                continue;
            }

            else{

                my_tokens.push_back(Token(STRING, str, startingLineNum));

                break;
            }
        }

        else{

            curr = in.getNextChar();
            //cout << (int) curr << endl;

            str += curr;
        }
    }
}

vector<Token> Scanner::getTokens(){

    return my_tokens;

}




