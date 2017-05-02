#ifndef DB07_LEXER_H
#define DB07_LEXER_H

#include<string>
#include<regex>
#include<cctype>
#include<list>
#include "token_type.h"

namespace db07 {
    class Lexer {
    public:
        void tokenize(std::string &, std::list<TokenType> &);

    private:
        bool is_delimiter(char chr);

        TokenType recognize_token_type(std::string &);
    };
}

#endif
