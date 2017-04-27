#ifndef DB07_LEXER_H
#define DB07_LEXER_H

#include <iostream>
#include<string>
#include<regex>
#include<cctype>

namespace db07 {
    class Lexer {
    public:
        enum TokenType {
            OPERATOR_EQ,
            OPERATOR_NEQ,
            KEYWORD_SELECT,
            KEYWORD_FROM,
            KEYWORD_WHERE,
            INTEGER,
            LITERAL,
            IDENTIFIER,
            UNRECOGNIZED
        };

        void tokenize(std::string &);

    private:

        bool is_delimiter(char chr);

        TokenType recognize_lexeme(std::string &);
    };
}

#endif
