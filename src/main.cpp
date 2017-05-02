#include <iostream>
#include "parser/lexer.h"

int main(int argc, char **argv) {
    std::string input = "SELECT last_name FROM students WHERE first_name == 'Alex'";
    std::list<db07::TokenType> token_types;

    db07::Lexer lexer;
    lexer.tokenize(input, token_types);
    if (token_types.back() == db07::TokenType::UNRECOGNIZED) {
        std::cout << "[FAILED] Lexical analysis: Unrecognized token\n";
    } else {
        std::cout << "[ DONE ] Lexical analysis\n";
    }

    return 0;
}
