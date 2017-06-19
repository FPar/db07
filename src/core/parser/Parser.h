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

        bool lookahead_is_eof();

        bool lookahead_is(token_type type);

        std::string token_to_string(token_type type);

        bool parse_error(std::vector<token_type> expected, bool eof_allowed);

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

        bool from_id_space();

        bool from_id_comma();

        bool after_from();

        bool where();

        bool group_by();

        bool group_by_id();

        bool group_by_id_space();

        bool group_by_id_comma();

        bool order_by();

        bool order_by_id();

        bool order_by_id_space();

        bool order_by_id_ascdesc();

        bool order_by_id_ascdesc_space();

        bool order_by_id_comma();
    };
}

#endif
