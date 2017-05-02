#include <iostream>
#include "parser/lexer.h"

int main(int argc, char **argv) {
    std::string input = "SELECT last_name FROM students WHERE first_name == 'Alex'";

    db07::Lexer lexer;
    std::list<db07::Token> tokens = lexer.tokenize(input);
    if (tokens.back().type() == db07::TokenType::UNRECOGNIZED) {
        std::cout << "[FAILED] Lexical analysis: Unrecognized token\n";
    } else {
        std::cout << "[ DONE ] Lexical analysis\n";
    }

    return 0;
}
