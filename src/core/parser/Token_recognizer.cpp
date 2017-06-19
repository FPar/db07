#include "parser/Token_recognizer.h"
#include "String_recognition_rule.h"
#include "Regex_recognition_rule.h"

namespace db07 {
    const std::vector<Recognition_rule *> Token_recognizer::RULES = {
            new Regex_recognition_rule("\\s+", token_type::WHITESPACE, [](const std::string &token_string) {
                for (const auto &token_chr : token_string) {
                    if (!isspace(token_chr)) {
                        return false;
                    }
                }
                return true;
            }),
            new String_recognition_rule("(", token_type::LEFT_BRACKET),
            new String_recognition_rule(")", token_type::RIGHT_BRACKET),
            new String_recognition_rule("=", token_type::OPERATOR_EQ),
            new String_recognition_rule("!=", token_type::OPERATOR_NEQ),
            new String_recognition_rule("<", token_type::OPERATOR_LT),
            new String_recognition_rule("<=", token_type::OPERATOR_LE),
            new String_recognition_rule(">=", token_type::OPERATOR_GE),
            new String_recognition_rule(">", token_type::OPERATOR_GT),
            new String_recognition_rule("*", token_type::STAR),
            new String_recognition_rule("AND", token_type::OPERATOR_AND),
            new String_recognition_rule("OR", token_type::OPERATOR_OR),
            new String_recognition_rule("NOT", token_type::OPERATOR_NOT),
            new String_recognition_rule("IN", token_type::OPERATOR_IN),
            new String_recognition_rule("SELECT", token_type::SELECT),
            new String_recognition_rule("DISTINCT", token_type::DISTINCT),
            new String_recognition_rule(",", token_type::COMMA),
            new String_recognition_rule("AS", token_type::AS),
            new String_recognition_rule("FROM", token_type::FROM),
            new String_recognition_rule("WHERE", token_type::WHERE),
            new Regex_recognition_rule("[0-9]+", token_type::INTEGER_LITERAL, [](const std::string &token_string) {
                for (const auto &token_chr : token_string) {
                    if (!isdigit(token_chr)) {
                        return false;
                    }
                }
                return true;
            }),
            new Regex_recognition_rule("\'[^\']*\'", token_type::STRING_LITERAL, [](const std::string &token_string) {
                bool starts_with_apostrophe = token_string.front() == '\'';
                unsigned long pos_second_apostrophe = token_string.find_first_of('\'', 1);
                bool has_second_apostrophe = pos_second_apostrophe != std::string::npos;
                bool ends_with_apostrophe = pos_second_apostrophe == token_string.length() - 1;

                return starts_with_apostrophe && (!has_second_apostrophe || ends_with_apostrophe);
            }),
            new Regex_recognition_rule("[a-z][a-z0-9_]*", token_type::IDENTIFIER, [](const std::string &token_string) {
                for (auto token_chr = token_string.begin(); token_chr != token_string.end(); token_chr++) {
                    if ((token_chr == token_string.begin() && !isalpha(*token_chr))
                        || !isalnum(*token_chr)) {
                        return false;
                    }
                }
                return true;
            })
    };

    token_type Token_recognizer::recognize(const std::string &token_string) {
        for (const auto &rule : RULES) {
            if (rule->matches(token_string)) {
                return rule->type();
            }
        }
        return token_type::UNRECOGNIZED;
    }

    bool Token_recognizer::can_recognize(const std::string &token_string) {
        for (const auto &rule : RULES) {
            if (rule->can_match(token_string)) {
                return true;
            }
        }
        return false;
    }
}