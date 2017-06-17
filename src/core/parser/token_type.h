#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

namespace db07 {
    enum class token_type {
        WHITESPACE,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        STAR,
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
        SELECT,
        DISTINCT,
        COMMA,
        AS,
        FROM,
        WHERE,
        INTEGER_LITERAL,
        STRING_LITERAL,
        IDENTIFIER,
        UNRECOGNIZED
    };
}

#endif
