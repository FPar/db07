#ifndef DB07_REGEX_TOKEN_RULE_H
#define DB07_REGEX_TOKEN_RULE_H

#include <regex>
#include "Token_rule.h"

namespace db07 {
    class Regex_token_rule : public Token_rule {
    private:
        const std::regex _regex;
        const std::function<bool(std::string &)> _can_match_predicate;

    public:
        Regex_token_rule(const std::string regex_str, const token_type token_type,
                         const std::function<bool(std::string &)> &can_match_predicate);

        bool matches(std::string &token_string) const override;

        bool can_match(std::string &token_string) const override;
    };
}

#endif
