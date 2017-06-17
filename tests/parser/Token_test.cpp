#include <functional>
#include <catch.h>
#include "parser/Token.h"

namespace db07 {
    TEST_CASE("token_ctor_no_value") {
        Token token = Token(token_type::IDENTIFIER);

        CHECK(token.type() == token_type::IDENTIFIER);
        CHECK(token.int_value() == 0);
        CHECK(token.string_value() == "");
    }

    TEST_CASE("token_ctor_string_value") {
        std::string token_string = "identifier";
        Token token = Token(token_type::IDENTIFIER, token_string);

        CHECK(token.type() == token_type::IDENTIFIER);
        CHECK(token.int_value() == 0);
        CHECK(token.string_value() == token_string);
    }

    TEST_CASE("token_ctor_int_value") {
        Token token = Token(token_type::INTEGER_LITERAL, 42);

        CHECK(token.type() == token_type::INTEGER_LITERAL);
        CHECK(token.int_value() == 42);
        CHECK(token.string_value() == "");
    }

    TEST_CASE("token_ctor_no_token_type_check") {
        std::string token_string = "invalid_integer";
        Token token = Token(token_type::INTEGER_LITERAL, token_string);

        CHECK(token.type() == token_type::INTEGER_LITERAL);
        CHECK(token.int_value() == 0);
        CHECK(token.string_value() == token_string);
    }
}