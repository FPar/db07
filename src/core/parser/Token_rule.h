#ifndef DB07_TOKEN_RULE_H
#define DB07_TOKEN_RULE_H

#include <functional>
#include "token_type.h"

namespace db07 {
    class Token_rule {
    private:
        const std::function<bool(std::string & )> _predicate;
        const token_type _token_type;
    public:
        Token_rule(const std::function<bool(std::string & )> &predicate_, const token_type token_type_)
                : _predicate(predicate_), _token_type(token_type_) {}

        bool matches(std::string &token_string) const;

        token_type type() const;
    };
}

#endif
