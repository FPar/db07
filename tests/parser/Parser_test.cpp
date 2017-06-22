#include <parser/Lexer.h>
#include "catch.h"
#include "parser/Parser.h"

namespace db07 {
    TEST_CASE("parser_select_from") {
        std::string input = "SELECT tesr  AS a, lastname FROM students , a ,b WHERE ((NOT A=1 AND NOT A=1) OR A=2)";
        Lexer lexer;
        auto tokens = lexer.tokenize(input);
        Parser parser;
        parser.parse(tokens);
    }
}