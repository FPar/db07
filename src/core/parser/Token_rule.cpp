#include "Token_rule.h"

namespace db07 {
    Token_rule::Token_rule(const token_type token_type_)
            : _token_type(token_type_) {}

    token_type Token_rule::type() const {
        return _token_type;
    }
}