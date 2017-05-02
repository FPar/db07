#ifndef DB07_TOKEN_EVALUATOR_H
#define DB07_TOKEN_EVALUATOR_H

#include <functional>
#include "token.h"

namespace db07 {
    class TokenEvaluator {
    public:
        static std::function<Token(std::string &)> for_type(TokenType token_type) {
            switch (token_type) {
                case TokenType::OPERATOR_EQ:
                case TokenType::OPERATOR_NEQ:
                case TokenType::OPERATOR_LT:
                case TokenType::OPERATOR_LE:
                case TokenType::OPERATOR_GE:
                case TokenType::OPERATOR_GT:
                case TokenType::OPERATOR_AND:
                case TokenType::OPERATOR_OR:
                case TokenType::OPERATOR_NOT:
                case TokenType::OPERATOR_IN:
                case TokenType::KEYWORD_SELECT:
                case TokenType::KEYWORD_DISTINCT:
                case TokenType::KEYWORD_FROM:
                case TokenType::KEYWORD_WHERE:
                    return [token_type](std::string &) { return Token(token_type); };
                case TokenType::INTEGER:
                    return [token_type](std::string &token_string) {
                        int int_value = std::stoi(token_string);
                        return Token(token_type, int_value);
                    };
                case TokenType::LITERAL:
                    return [token_type](std::string &token_string) {
                        std::string string_value = token_string.substr(1, token_string.length() - 2);
                        return Token(token_type, string_value);
                    };
                case TokenType::IDENTIFIER:
                case TokenType::UNRECOGNIZED:
                default:
                    return [token_type](std::string &token_string) { return Token(token_type, token_string); };
            }
        }
    };
}

#endif
