#include "String_token_rule.h"

namespace db07 {
    String_token_rule::String_token_rule(const std::string string_representation, const token_type token_type)
            : Token_rule(token_type),
              _string_representation(string_representation) {}

    bool String_token_rule::matches(std::string &token_string) const {
        return _string_representation.compare(token_string) == 0;
    }

    bool String_token_rule::can_match(std::string &token_string) const {
        return _string_representation.compare(0, token_string.length(), token_string) == 0;
    }
}