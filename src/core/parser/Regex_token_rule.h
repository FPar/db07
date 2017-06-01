#ifndef DB07_REGEX_TOKEN_RULE_H
#define DB07_REGEX_TOKEN_RULE_H

#include <regex>
#include "Token_rule.h"

namespace db07 {
    class Regex_token_rule : public Token_rule {
    private:
        std::regex _regex;

    public:
        Regex_token_rule(const char *regex_str, const token_type token_type);

        bool matches(std::string &token_string) const override;
    };
}

#endif
