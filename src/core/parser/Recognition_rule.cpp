#include "Recognition_rule.h"

namespace db07 {
    Recognition_rule::Recognition_rule(const token_type token_type_)
            : _token_type(token_type_) {}

    token_type Recognition_rule::type() const {
        return _token_type;
    }
}