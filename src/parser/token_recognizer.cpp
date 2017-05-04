#include "token_recognizer.h"

namespace db07 {
    static const std::regex REGEX_INTEGER{"[0-9]+", std::regex_constants::icase};
    static const std::regex REGEX_LITERAL{"\'.*\'", std::regex_constants::icase};
    static const std::regex REGEX_IDENTIFIER{"[a-z][a-z0-9_]*", std::regex_constants::icase};

    const std::list<TokenRecognizer::Rule> TokenRecognizer::RULES = {
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("=") == 0; }, TokenType::OPERATOR_EQ},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("!=") == 0; }, TokenType::OPERATOR_NEQ},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("<") == 0; }, TokenType::OPERATOR_LT},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("<=") == 0; }, TokenType::OPERATOR_LE},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare(">=") == 0; }, TokenType::OPERATOR_GE},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare(">") == 0; }, TokenType::OPERATOR_GT},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("AND") == 0; }, TokenType::OPERATOR_AND},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("OR") == 0; }, TokenType::OPERATOR_OR},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("NOT") == 0; }, TokenType::OPERATOR_NOT},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("IN") == 0; }, TokenType::OPERATOR_IN},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("SELECT") == 0; }, TokenType::KEYWORD_SELECT},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("DISTINCT") == 0; }, TokenType::KEYWORD_DISTINCT},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("FROM") == 0; }, TokenType::KEYWORD_FROM},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("WHERE") == 0; }, TokenType::KEYWORD_WHERE},
            TokenRecognizer::Rule {[](std::string &token_string) { return std::regex_match(token_string, REGEX_INTEGER); }, TokenType::INTEGER},
            TokenRecognizer::Rule {[](std::string &token_string) { return std::regex_match(token_string, REGEX_LITERAL); }, TokenType::LITERAL},
            TokenRecognizer::Rule {[](std::string &token_string) { return std::regex_match(token_string, REGEX_IDENTIFIER); }, TokenType::IDENTIFIER},
    };

    TokenRecognizer::Rule::Rule(const std::function<bool(std::string &)> &predicate_, const TokenType token_type_)
            : predicate_(predicate_), token_type_(token_type_) {}

    bool TokenRecognizer::Rule::matches(std::string &token_string) const {
        return predicate_(token_string);
    }

    TokenType TokenRecognizer::Rule::token_type() const {
        return token_type_;
    }

    TokenType TokenRecognizer::recognize(std::string &token_string) {
        for (std::list<Rule>::const_iterator rule = TokenRecognizer::RULES.begin();
             rule != TokenRecognizer::RULES.end();
             rule++) {
            if (rule->matches(token_string)) {
                return rule->token_type();
            }
        }
        return TokenType::UNRECOGNIZED;
    }
}