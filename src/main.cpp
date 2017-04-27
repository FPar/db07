#include "parser/lexer.h"

int main(int argc, char **argv) {
    std::string input = "SELECT last_name FROM students WHERE first_name == 'Alex'";

    db07::Lexer lexer;
    lexer.tokenize(input);

    return 0;
}
