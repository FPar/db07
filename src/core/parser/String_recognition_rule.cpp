#include "String_recognition_rule.h"

namespace db07 {
    String_recognition_rule::String_recognition_rule(const std::string string_representation, const token_type token_type)
            : Recognition_rule(token_type),
              _string_representation(string_representation) {}

    bool String_recognition_rule::matches(const std::string &token_string) const {
        return _string_representation.compare(token_string) == 0;
    }

    bool String_recognition_rule::can_match(const std::string &token_string) const {
        return _string_representation.compare(0, token_string.length(), token_string) == 0;
    }
}