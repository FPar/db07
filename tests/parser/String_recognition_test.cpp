#include "catch.h"
#include "parser/String_recognition_rule.h"

namespace db07 {
    TEST_CASE("Token type 2") {
        String_recognition_rule rule("AND", token_type::OPERATOR_AND);

        CHECK(rule.type() == token_type::OPERATOR_AND);
    }

    TEST_CASE("String comparison used for match recognition") {
        String_recognition_rule rule("AND", token_type::OPERATOR_AND);

        CHECK_FALSE(rule.matches(""));
        CHECK_FALSE(rule.matches("A"));
        CHECK_FALSE(rule.matches("AN"));
        CHECK(rule.matches("AND"));
        CHECK_FALSE(rule.matches("ANDI"));
        CHECK_FALSE(rule.matches("AND I"));
        CHECK_FALSE(rule.matches("AND "));
        CHECK_FALSE(rule.matches(" AND"));
        CHECK_FALSE(rule.matches(" AND "));
    }

    TEST_CASE("String start with used for possible match recognition") {
        String_recognition_rule rule("AND", token_type::OPERATOR_AND);

        CHECK(rule.can_match(""));
        CHECK(rule.can_match("A"));
        CHECK(rule.can_match("AN"));
        CHECK(rule.can_match("AND"));
        CHECK_FALSE(rule.can_match("ANDI"));
        CHECK_FALSE(rule.can_match("AND I"));
        CHECK_FALSE(rule.can_match("AND "));
        CHECK_FALSE(rule.can_match(" AND"));
        CHECK_FALSE(rule.can_match(" AND "));
    }
}