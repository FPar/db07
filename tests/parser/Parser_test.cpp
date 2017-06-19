#include "catch.h"
#include "parser/Parser.h"

namespace db07 {
    TEST_CASE("parser_select_from") {
        std::vector<Token> tokens;
        tokens.push_back(Token(token_type::SELECT));
        tokens.push_back(Token(token_type::WHITESPACE));
        tokens.push_back(Token(token_type::STAR));
        tokens.push_back(Token(token_type::WHITESPACE));
        tokens.push_back(Token(token_type::FROM));
        tokens.push_back(Token(token_type::WHITESPACE));
        tokens.push_back(Token(token_type::IDENTIFIER));
        tokens.push_back(Token(token_type::WHERE));
        tokens.push_back(Token(token_type::IDENTIFIER));
        Parser parser;
        parser.parse(tokens);
    }
}