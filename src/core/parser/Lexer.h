#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "parser/Token_evaluator.h"

namespace db07 {
    class Lexer {
    public:
        std::vector<Token> tokenize(std::string &input);
    };
}

#endif
