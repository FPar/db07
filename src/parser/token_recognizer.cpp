#include "token_recognizer.h"

namespace db07 {
    const std::regex TokenRecognizer::REGEX_INTEGER{"[0-9]+", std::regex_constants::icase};
    const std::regex TokenRecognizer::REGEX_LITERAL{"\'.*\'", std::regex_constants::icase};
    const std::regex TokenRecognizer::REGEX_IDENTIFIER{"[a-z][a-z0-9_]*", std::regex_constants::icase};

    const std::list<TokenRecognizer::Rule> TokenRecognizer::RULES = {
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("==") == 0; }, TokenType::OPERATOR_EQ},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("!=") == 0; }, TokenType::OPERATOR_NEQ},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("SELECT") == 0; }, TokenType::KEYWORD_SELECT},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("FROM") == 0; }, TokenType::KEYWORD_FROM},
            TokenRecognizer::Rule {[](std::string &token_string) { return token_string.compare("WHERE") == 0; }, TokenType::KEYWORD_WHERE},
            TokenRecognizer::Rule {[](std::string &token_string) { return std::regex_match(token_string, TokenRecognizer::REGEX_INTEGER); }, TokenType::INTEGER},
            TokenRecognizer::Rule {[](std::string &token_string) { return std::regex_match(token_string, TokenRecognizer::REGEX_LITERAL); }, TokenType::LITERAL},
            TokenRecognizer::Rule {[](std::string &token_string) { return std::regex_match(token_string, TokenRecognizer::REGEX_IDENTIFIER); }, TokenType::IDENTIFIER},
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