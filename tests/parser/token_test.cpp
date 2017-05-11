#include "catch.h"
#include "parser/token.h"
#include <functional>

namespace db07 {
    TEST_CASE("token_ctor_no_value", "[Token]") {
        Token token = Token(TokenType::IDENTIFIER);

        CHECK(token.type() == TokenType::IDENTIFIER);
        CHECK(token.int_value() == 0);
        CHECK(token.string_value() == "");
    }

    TEST_CASE("token_ctor_string_value", "[Token]") {
        std::string token_string = "identifier";
        Token token = Token(TokenType::IDENTIFIER, token_string);

        CHECK(token.type() == TokenType::IDENTIFIER);
        CHECK(token.int_value() == 0);
        CHECK(token.string_value() == token_string);
    }

    TEST_CASE("token_ctor_int_value", "[Token]") {
        Token token = Token(TokenType::INTEGER, 42);

        CHECK(token.type() == TokenType::INTEGER);
        CHECK(token.int_value() == 42);
        CHECK(token.string_value() == "");
    }

    TEST_CASE("token_ctor_no_token_type_check", "[Token]") {
        std::string token_string = "invalid_integer";
        Token token = Token(TokenType::INTEGER, token_string);

        CHECK(token.type() == TokenType::INTEGER);
        CHECK(token.int_value() == 0);
        CHECK(token.string_value() == token_string);
    }
}