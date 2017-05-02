#include "token.h"

namespace db07 {
    Token::Token(const TokenType type_)
            : type_(type_) {}

    TokenType Token::type() const {
        return type_;
    }
}