#ifndef DB07_STRING_TOKEN_RULE_H
#define DB07_STRING_TOKEN_RULE_H

#include "Recognition_rule.h"

namespace db07 {
    class String_recognition_rule : public Recognition_rule {
    private:
        const std::string _string_representation;

    public:
        String_recognition_rule(const std::string string_representation, const token_type token_type);

        bool matches(const std::string &token_string) const override;

        bool can_match(const std::string &token_string) const override;
    };
}

#endif
