#include <string>
#include <vector>
#include <regex>
#include <stdexcept>

using std::string;
using std::vector;
using std::regex_match;
using std::regex;
using std::runtime_error;


class Token {
public:
    string type;
    string value;
    Token(string t, string v) :type(t), value(v) {}
};

class AST {
public:
};

vector<Token> tokenizer(string);
AST parser(vector<Token>);
AST transformer(AST);
string codeGenerator(AST);

vector<Token> tokenizer(string input) {
    int current = 0;
    vector<Token> tokens;
    while (current < input.size()) {
        string curr_char = string(1, input[current]);

        if (curr_char == "(") {
            tokens.push_back(Token("paren", "("));
            ++current;
            continue;
        }

        if (curr_char == ")") {
            tokens.push_back(Token("paren", ")"));
            ++current;
            continue;
        }

        /* WHITESPACE  */
        if (regex_match(curr_char, regex("\s"))) {
            current++;
            continue;
        }

        /* NUMBERS  */
        if (regex_match(curr_char, regex("[0-9]"))) {
            string value;
            while (regex_match(curr_char, regex("[0-9]"))) {
                value += curr_char;
                curr_char = input[++current];
            }

            tokens.push_back(Token("number", value));
            continue;
        }

        /* STRINGS */
        if (curr_char == "\"") {
            string value;
            curr_char = input[++current];

            while (curr_char != "\"") {
                value += curr_char;
                curr_char = input[++current];
            }

            curr_char = input[++current];
            tokens.push_back(Token("string", value));
            continue;
        }

        /* LETTERS */
        if (regex_match(curr_char, regex("[a-z]"))) {
            string value;
            curr_char = input[++current];

            while (regex_match(curr_char, regex("[a-z]"))) {
                value += curr_char;
                curr_char = input[++current];
            }

            tokens.push_back(Token("name", value));
            continue;
        }

        throw runtime_error("I dont know what this character is: " + curr_char);
    }
    return tokens;
}


