#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <regex>
#include <cctype>
#include <list>
#include <memory>
#include "parser/Token_evaluator.h"

namespace db07 {
    class Lexer {
    public:
        std::list<Token> tokenize(std::string &);

    private:
        bool is_delimiter(char chr);
    };
}

#endif
