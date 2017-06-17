#include "catch.h"
#include "parser/Regex_recognition_rule.h"

namespace db07 {
    TEST_CASE("Token type") {
        Regex_recognition_rule rule(".*", token_type::INTEGER, [](const std::string &token_string) { return false; });

        CHECK(rule.type() == token_type::INTEGER);
    }

    TEST_CASE("Regex used for match recognition") {
        Regex_recognition_rule rule("[0-9][0-9]+", token_type::INTEGER,
                                    [](const std::string &token_string) { return false; });

        CHECK_FALSE(rule.matches("4"));
        CHECK(rule.matches("42"));
        CHECK(rule.matches("421"));
        CHECK_FALSE(rule.matches("42 1"));
        CHECK_FALSE(rule.matches("421 "));
        CHECK_FALSE(rule.matches(" 421"));
        CHECK_FALSE(rule.matches(" 421 "));
    }

    TEST_CASE("Regex is case insensitive") {
        Regex_recognition_rule rule("AND", token_type::OPERATOR_AND,
                                    [](const std::string &token_string) { return false; });

        CHECK(rule.matches("and"));
        CHECK(rule.matches("And"));
        CHECK(rule.matches("AND"));
    }

    TEST_CASE("Predicate used for possible match recognition") {
        Regex_recognition_rule rule(".*", token_type::LITERAL, [](const std::string &token_string) {
            return !token_string.empty() && token_string.front() == 'a';
        });

        CHECK_FALSE(rule.can_match(""));
        CHECK(rule.can_match("a"));
        CHECK(rule.can_match("ab"));
        CHECK_FALSE(rule.can_match("b"));
    }
}