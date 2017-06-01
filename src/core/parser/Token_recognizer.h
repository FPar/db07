#ifndef TOKEN_RECOGNIZER_H
#define TOKEN_RECOGNIZER_H

#include <list>
#include "token_type.h"
#include "Recognition_rule.h"

namespace db07 {
    class Token_recognizer {
    private:
        static const std::list<Recognition_rule *> RULES;

    public:
        static token_type recognize(const std::string &token_string);

        static bool can_recognize(const std::string &token_string);
    };
}

#endif
