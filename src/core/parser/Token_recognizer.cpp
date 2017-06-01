#include "parser/Token_recognizer.h"
#include "String_token_rule.h"
#include "Regex_token_rule.h"

namespace db07 {
    const std::list<Token_rule *> Token_recognizer::RULES = {
            new String_token_rule("=", token_type::OPERATOR_EQ),
            new String_token_rule("!=", token_type::OPERATOR_NEQ),
            new String_token_rule("<", token_type::OPERATOR_LT),
            new String_token_rule("<=", token_type::OPERATOR_LE),
            new String_token_rule(">=", token_type::OPERATOR_GE),
            new String_token_rule(">", token_type::OPERATOR_GT),
            new String_token_rule("AND", token_type::OPERATOR_AND),
            new String_token_rule("OR", token_type::OPERATOR_OR),
            new String_token_rule("NOT", token_type::OPERATOR_NOT),
            new String_token_rule("IN", token_type::OPERATOR_IN),
            new String_token_rule("SELECT", token_type::KEYWORD_SELECT),
            new String_token_rule("DISTINCT", token_type::KEYWORD_DISTINCT),
            new String_token_rule("FROM", token_type::KEYWORD_FROM),
            new String_token_rule("WHERE", token_type::KEYWORD_WHERE),
            new Regex_token_rule("[0-9]+", token_type::INTEGER, [](std::string &token_string) {
                for (auto token_chr = token_string.begin(); token_chr != token_string.end(); token_chr++) {
                    if (isdigit(*token_chr)) {
                        return false;
                    }
                }
                return true;
            }),
            new Regex_token_rule("\'.*\'", token_type::LITERAL, [](std::string &token_string) {
                return token_string.front() == '\'';
            }),
            new Regex_token_rule("[a-z][a-z0-9_]*", token_type::IDENTIFIER, [](std::string &token_string) {
                for (auto token_chr = token_string.begin(); token_chr != token_string.end(); token_chr++) {
                    if ((token_chr == token_string.begin() && !isalpha(*token_chr))
                        || !isalnum(*token_chr)) {
                        return false;
                    }
                }
                return true;
            })
    };

    token_type Token_recognizer::recognize(std::string &token_string) {
        for (auto rule = Token_recognizer::RULES.begin();
             rule != Token_recognizer::RULES.end();
             rule++) {
            if ((*rule)->matches(token_string)) {
                return (*rule)->type();
            }
        }
        return token_type::UNRECOGNIZED;
    }
}