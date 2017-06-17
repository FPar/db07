#include "catch.h"
#include "parser/Token_recognizer.h"

namespace db07 {
    TEST_CASE("Recognize tokens") {
        SECTION("Whitespace") {
            CHECK(Token_recognizer::recognize(" ") == token_type::WHITESPACE);
            CHECK(Token_recognizer::recognize("  ") == token_type::WHITESPACE);
            CHECK(Token_recognizer::recognize("\t") == token_type::WHITESPACE);
            CHECK(Token_recognizer::recognize("\n") == token_type::WHITESPACE);
            CHECK(Token_recognizer::recognize("\n\r") == token_type::WHITESPACE);
            CHECK(Token_recognizer::recognize(" \n ") == token_type::WHITESPACE);

            CHECK(Token_recognizer::recognize("") == token_type::UNRECOGNIZED);
            CHECK(Token_recognizer::recognize("a") == token_type::UNRECOGNIZED);
            CHECK(Token_recognizer::recognize("a") == token_type::UNRECOGNIZED);
            CHECK(Token_recognizer::recognize("a") == token_type::UNRECOGNIZED);
        }
    }
}