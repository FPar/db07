#include "catch.h"
#include "parser/token_evaluator.h"

namespace db07 {
    void no_value(token_type token_type, std::string token_type_name) {
        SECTION("no_value" + token_type_name) {
            std::string token_string = "KEYWORD";
            auto evaluator = Token_evaluator::for_type(token_type);
            Token token = evaluator(token_string);

            REQUIRE(evaluator != nullptr);
            CHECK(token.type() == token_type);
            CHECK(token.string_value() == "");
            CHECK(token.int_value() == 0);
        }
    }

    void int_literal(token_type token_type, std::string token_type_name) {
        SECTION("int_literal" + token_type_name) {
            std::string token_string = "42";
            auto evaluator = Token_evaluator::for_type(token_type);
            Token token = evaluator(token_string);

            REQUIRE(evaluator != nullptr);
            CHECK(token.type() == token_type);
            CHECK(token.string_value() == "");
            CHECK(token.int_value() == 42);
        }
    }

    void string_literal(token_type token_type, std::string token_type_name) {
        SECTION("string_literal" + token_type_name) {
            std::string token_string = "'Alex'";
            auto evaluator = Token_evaluator::for_type(token_type);
            Token token = evaluator(token_string);

            REQUIRE(evaluator != nullptr);
            CHECK(token.type() == token_type);
            CHECK(token.string_value() == "Alex");
            CHECK(token.int_value() == 0);
        }
    }

    void string_value(token_type token_type, std::string token_type_name) {
        SECTION("string_value" + token_type_name) {
            std::string token_string = "students";
            auto evaluator = Token_evaluator::for_type(token_type);
            Token token = evaluator(token_string);

            REQUIRE(evaluator != nullptr);
            CHECK(token.type() == token_type);
            CHECK(token.string_value() == token_string);
            CHECK(token.int_value() == 0);
        }
    }

    TEST_CASE("token_evaluator_no_value", "[TokenEvaluator]") {
        no_value(token_type::OPERATOR_EQ, "OPERATOR_EQ");
        no_value(token_type::OPERATOR_NEQ, "OPERATOR_NEQ");
        no_value(token_type::OPERATOR_LT, "OPERATOR_LT");
        no_value(token_type::OPERATOR_LE, "OPERATOR_LE");
        no_value(token_type::OPERATOR_GE, "OPERATOR_GE");
        no_value(token_type::OPERATOR_GT, "OPERATOR_GT");
        no_value(token_type::OPERATOR_AND, "OPERATOR_AND");
        no_value(token_type::OPERATOR_OR, "OPERATOR_OR");
        no_value(token_type::OPERATOR_NOT, "OPERATOR_NOT");
        no_value(token_type::OPERATOR_IN, "OPERATOR_IN");
        no_value(token_type::KEYWORD_SELECT, "KEYWORD_SELECT");
        no_value(token_type::KEYWORD_DISTINCT, "KEYWORD_DISTINCT");
        no_value(token_type::KEYWORD_FROM, "KEYWORD_FROM");
        no_value(token_type::KEYWORD_WHERE, "KEYWORD_WHERE");
    }

    TEST_CASE("token_evaluator_int_literal", "[TokenEvaluator]") {
        int_literal(token_type::INTEGER, "INTEGER");
    }

    TEST_CASE("token_evaluator_string_literal", "[TokenEvaluator]") {
        string_literal(token_type::LITERAL, "LITERAL");
    }

    TEST_CASE("token_evaluator_string_value", "[TokenEvaluator]") {
        string_value(token_type::IDENTIFIER, "IDENTIFIER");
        string_value(token_type::UNRECOGNIZED, "UNRECOGNIZED");
    }
}