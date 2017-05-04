#ifndef DB07_TOKEN_TYPE_H
#define DB07_TOKEN_TYPE_H

namespace db07 {
    enum class TokenType {
        OPERATOR_EQ,
        OPERATOR_NEQ,
        OPERATOR_LT,
        OPERATOR_LE,
        OPERATOR_GE,
        OPERATOR_GT,
        OPERATOR_AND,
        OPERATOR_OR,
        OPERATOR_NOT,
        OPERATOR_IN,
        KEYWORD_SELECT,
        KEYWORD_DISTINCT,
        KEYWORD_FROM,
        KEYWORD_WHERE,
        INTEGER,
        LITERAL,
        IDENTIFIER,
        UNRECOGNIZED
    };
}

#endif