#include "parser/Token.h"

namespace db07 {
    Token::Token(const token_type type)
            : _type(type), _string_value(""), _int_value(0) {}

    Token::Token(const token_type type, std::string &string_value)
            : _type(type), _string_value(string_value), _int_value(0) {}

    Token::Token(const token_type type, int int_value)
            : _type(type), _string_value(""), _int_value(int_value) {}

    token_type Token::type() const {
        return _type;
    }

    std::string Token::string_value() const {
        return _string_value;
    }

    int Token::int_value() const {
        return _int_value;
    }
}