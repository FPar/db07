#ifndef TOKEN_RECOGNIZER_H
#define TOKEN_RECOGNIZER_H

#include <string>
#include <functional>
#include <list>
#include <regex>
#include "token_type.h"
#include "Token_rule.h"

namespace db07 {
    class Token_recognizer {
    private:

        static const std::list<Token_rule> RULES;

    public:
        static token_type recognize(std::string &token_string);
    };
}

#endif
