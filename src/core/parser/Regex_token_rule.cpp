#include "Regex_token_rule.h"

namespace db07 {
    Regex_token_rule::Regex_token_rule(const char *regex_str, const token_type token_type)
            : Token_rule(token_type),
              _regex(regex_str, std::regex_constants::icase) {}

    bool Regex_token_rule::matches(std::string &token_string) const {
        return std::regex_match(token_string, _regex);
    }
}
