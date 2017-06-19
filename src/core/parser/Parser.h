#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"

namespace db07 {
    class Parser {
    private:
        std::vector<Token>::const_iterator _lookahead;
        std::vector<Token>::const_iterator _end;

    public:
        void parse(std::vector<Token> &tokens);

    private:
        bool sql();

        bool lookahead_is(token_type type);

        std::string token_to_string(token_type type);

        bool parse_error(std::vector<token_type> expected);

        bool terminal(token_type type);

        bool select();

        bool optional_distinct();

        bool projection();

        bool projection_list();

        bool optional_renaming();

        bool optional_projection_list();
    };
}

#endif
