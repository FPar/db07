#ifndef TOKEN_EVALUATOR_H
#define TOKEN_EVALUATOR_H

#include <functional>
#include "parser/Token.h"

namespace db07 {
    class Token_evaluator {
    public:
        static std::function<Token(std::string &)> for_type(token_type token_type);
    };
}

#endif
