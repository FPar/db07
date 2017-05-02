#ifndef DB07_TOKEN_H
#define DB07_TOKEN_H

#include <string>
#include "token_type.h"

namespace db07 {
    class Token {
    private:
        const TokenType type_;

    public:
        Token(const TokenType type_);

        TokenType type() const;
    };
}

#endif
