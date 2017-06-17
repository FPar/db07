#ifndef TOKEN_EVALUATOR_H
#define TOKEN_EVALUATOR_H

#include <functional>
#include "parser/Token.h"

namespace db07 {
    class Token_evaluator {
    public:
        static std::function<Token(std::string &)> for_type(token_type token_type) {
            switch (token_type) {
                case token_type::WHITESPACE:
                case token_type::LEFT_BRACKET:
                case token_type::RIGHT_BRACKET:
                case token_type::STAR:
                case token_type::OPERATOR_EQ:
                case token_type::OPERATOR_NEQ:
                case token_type::OPERATOR_LT:
                case token_type::OPERATOR_LE:
                case token_type::OPERATOR_GE:
                case token_type::OPERATOR_GT:
                case token_type::OPERATOR_AND:
                case token_type::OPERATOR_OR:
                case token_type::OPERATOR_NOT:
                case token_type::OPERATOR_IN:
                case token_type::SELECT:
                case token_type::DISTINCT:
                case token_type::COMMA:
                case token_type::AS:
                case token_type::FROM:
                case token_type::WHERE:
                    return [token_type](std::string &) { return Token(token_type); };
                case token_type::INTEGER_LITERAL:
                    return [token_type](std::string &token_string) {
                        int int_value = std::stoi(token_string);
                        return Token(token_type, int_value);
                    };
                case token_type::STRING_LITERAL:
                    return [token_type](std::string &token_string) {
                        std::string string_value = token_string.substr(1, token_string.length() - 2);
                        return Token(token_type, string_value);
                    };
                case token_type::IDENTIFIER:
                default:
                case token_type::UNRECOGNIZED:
                    return [token_type](std::string &token_string) { return Token(token_type, token_string); };
            }
        }
    };
}

#endif
