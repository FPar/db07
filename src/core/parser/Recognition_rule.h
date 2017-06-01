#ifndef DB07_TOKEN_RULE_H
#define DB07_TOKEN_RULE_H

#include <functional>
#include "token_type.h"

namespace db07 {
    class Recognition_rule {
    private:
        const token_type _token_type;

    public:
        Recognition_rule(const token_type token_type);

        token_type type() const;

        virtual bool matches(const std::string &token_string) const = 0;

        virtual bool can_match(const std::string &token_string) const = 0;
    };
}

#endif
