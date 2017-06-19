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

        bool distinct();

        bool projection();

        bool id_projection();

        bool id_space_projection();

        bool id_comma_projection();

        bool id_as_projection();

        bool id_as_space_projection();

        bool from();

        bool from_id();

        bool where();

        bool selection();

        bool condition();

        bool comp_op();

        bool condition_op();

        bool condition_rval();

        bool condition_end();
    };
}

#endif
