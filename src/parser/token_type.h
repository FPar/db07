#ifndef DB07_TOKEN_TYPE_H
#define DB07_TOKEN_TYPE_H

namespace db07 {
    enum class TokenType {
        OPERATOR_EQ,
        OPERATOR_NEQ,
        KEYWORD_SELECT,
        KEYWORD_FROM,
        KEYWORD_WHERE,
        INTEGER,
        LITERAL,
        IDENTIFIER,
        UNRECOGNIZED
    };
}

#endif
