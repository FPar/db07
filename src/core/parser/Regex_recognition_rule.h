#ifndef DB07_REGEX_TOKEN_RULE_H
#define DB07_REGEX_TOKEN_RULE_H

#include <regex>
#include "Recognition_rule.h"

namespace db07 {
    class Regex_recognition_rule : public Recognition_rule {
    private:
        const std::regex _regex;
        const std::function<bool(const std::string &)> _can_match_predicate;

    public:
        Regex_recognition_rule(const std::string regex_str, const token_type token_type,
                         const std::function<bool(const std::string &)> &can_match_predicate);

        bool matches(const std::string &token_string) const override;

        bool can_match(const std::string &token_string) const override;
    };
}

#endif
