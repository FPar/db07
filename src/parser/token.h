#ifndef DB07_TOKEN_H
#define DB07_TOKEN_H

#include <string>
#include "token_type.h"

namespace db07 {
    class Token {
    private:
        const TokenType type_;
        const std::string string_value_;
        const int int_value_;

    public:
        Token(const TokenType type_);

        Token(const TokenType type_, std::string &);

        Token(const TokenType type_, int);

        TokenType type() const;

        std::string string_value() const;

        int int_value() const;
    };
}

#endif
