#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <optimizer/Query_data.h>
#include "Token.h"

namespace db07 {
    class Parser {
    private:
        std::vector<Token>::const_iterator _lookahead;
        std::vector<Token>::const_iterator _end;
        Query_data _query_data;
        Query_condition _query_condition;

    public:
        void parse(std::vector<Token> &tokens);

        Query_data &query_data();

    private:
        void ensure_token_stream_not_empty();

        bool lookahead_is(token_type candidate);

        bool lookahead_is_one_of(std::vector<token_type> candidates);

        void throw_parse_error(std::vector<token_type> expected);

        void terminal(token_type expected);

        std::string terminal_string_value(token_type expected);

        int terminal_int_value(token_type expected);

        void sql();

        void select();

        void distinct();

        void projection();

        void id_projection();

        void id_space_projection();

        void id_comma_projection();

        void id_as_projection();

        void id_as_space_projection();

        void from();

        void from_id();

        void from_id_space();

        void from_id_comma();

        void after_from();

        void where();

        void where_expr();

        void where_expr_pos();

        void where_expr_open();

        void where_id();

        void where_comp();

        void where_id_comp();

        void where_rval();

        void where_id_comp_rval();

        void where_comp_space();

        void group_by();

        void group_by_id();

        void group_by_id_space();

        void group_by_id_comma();

        void order_by();

        void order_by_id();

        void order_by_id_space();

        void order_by_id_ascdesc();

        void order_by_id_ascdesc_space();

        void order_by_id_comma();
    };
}

#endif
