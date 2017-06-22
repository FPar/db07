#include <parser/Lexer.h>
#include <parser/parse_error.h>
#include <iostream>
#include "catch.h"
#include "parser/Parser.h"

namespace db07 {
    TEST_CASE("parser_select_from") {
        try {
            std::string input = "SELECT * FROM students";
            Lexer lexer;
            auto tokens = lexer.tokenize(input);
            Parser parser;
            parser.parse(tokens);
        } catch (parse_error e) {
            std::cout << "Parse error" << std::endl;
        }
    }
}