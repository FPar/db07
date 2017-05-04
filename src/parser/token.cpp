#include "token.h"

namespace db07 {
    Token::Token(const TokenType type)
            : type_(type), string_value_(""), int_value_(0) {}

    Token::Token(const TokenType type, std::string &string_value)
            : type_(type), string_value_(string_value), int_value_(0) {}

    Token::Token(const TokenType type, int int_value)
            : type_(type), string_value_(""), int_value_(int_value) {}

    TokenType Token::type() const {
        return type_;
    }

    std::string Token::string_value() const {
        return string_value_;
    }

    int Token::int_value() const {
        return int_value_;
    }
}