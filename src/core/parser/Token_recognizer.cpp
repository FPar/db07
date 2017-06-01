#include "parser/Token_recognizer.h"

namespace db07 {
    static const std::regex REGEX_INTEGER{"[0-9]+", std::regex_constants::icase};
    static const std::regex REGEX_LITERAL{"\'.*\'", std::regex_constants::icase};
    static const std::regex REGEX_IDENTIFIER{"[a-z][a-z0-9_]*", std::regex_constants::icase};

    const std::list<Token_rule> Token_recognizer::RULES = {
            Token_rule {[](std::string &token_string) { return token_string.compare("=") == 0; }, token_type::OPERATOR_EQ},
            Token_rule {[](std::string &token_string) { return token_string.compare("!=") == 0; }, token_type::OPERATOR_NEQ},
            Token_rule {[](std::string &token_string) { return token_string.compare("<") == 0; }, token_type::OPERATOR_LT},
            Token_rule {[](std::string &token_string) { return token_string.compare("<=") == 0; }, token_type::OPERATOR_LE},
            Token_rule {[](std::string &token_string) { return token_string.compare(">=") == 0; }, token_type::OPERATOR_GE},
            Token_rule {[](std::string &token_string) { return token_string.compare(">") == 0; }, token_type::OPERATOR_GT},
            Token_rule {[](std::string &token_string) { return token_string.compare("AND") == 0; }, token_type::OPERATOR_AND},
            Token_rule {[](std::string &token_string) { return token_string.compare("OR") == 0; }, token_type::OPERATOR_OR},
            Token_rule {[](std::string &token_string) { return token_string.compare("NOT") == 0; }, token_type::OPERATOR_NOT},
            Token_rule {[](std::string &token_string) { return token_string.compare("IN") == 0; }, token_type::OPERATOR_IN},
            Token_rule {[](std::string &token_string) { return token_string.compare("SELECT") == 0; }, token_type::KEYWORD_SELECT},
            Token_rule {[](std::string &token_string) { return token_string.compare("DISTINCT") == 0; }, token_type::KEYWORD_DISTINCT},
            Token_rule {[](std::string &token_string) { return token_string.compare("FROM") == 0; }, token_type::KEYWORD_FROM},
            Token_rule {[](std::string &token_string) { return token_string.compare("WHERE") == 0; }, token_type::KEYWORD_WHERE},
            Token_rule {[](std::string &token_string) { return std::regex_match(token_string, REGEX_INTEGER); }, token_type::INTEGER},
            Token_rule {[](std::string &token_string) { return std::regex_match(token_string, REGEX_LITERAL); }, token_type::LITERAL},
            Token_rule {[](std::string &token_string) { return std::regex_match(token_string, REGEX_IDENTIFIER); }, token_type::IDENTIFIER},
    };

    bool Token_rule::matches(std::string &token_string) const {
        return _predicate(token_string);
    }

    token_type Token_rule::type() const {
        return _token_type;
    }

    token_type Token_recognizer::recognize(std::string &token_string) {
        for (std::list<Token_rule>::const_iterator rule = Token_recognizer::RULES.begin();
             rule != Token_recognizer::RULES.end();
             rule++) {
            if (rule->matches(token_string)) {
                return rule->type();
            }
        }
        return token_type::UNRECOGNIZED;
    }
}