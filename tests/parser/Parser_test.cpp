#include "catch.h"
#include "parser/Parser.h"

namespace db07 {
    TEST_CASE("parser_select_from") {
        std::list<Token> tokens;
        tokens.push_back(Token(token_type::KEYWORD_SELECT));
        tokens.push_back(Token(token_type::KEYWORD_FROM));
        tokens.push_back(Token(token_type::IDENTIFIER));
        tokens.push_back(Token(token_type::KEYWORD_WHERE));
        tokens.push_back(Token(token_type::IDENTIFIER));
        Parser parser;
        parser.parse(tokens);
    };
}