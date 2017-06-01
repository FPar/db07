#ifndef DB07_PARSER_H
#define DB07_PARSER_H

#include <list>
#include "Token.h"

namespace db07 {
    class Parser {
    private:
        std::list<Token>::const_iterator _lookahead;
        std::list<Token>::const_iterator _end;
    public:
        void parse(std::list<Token> &tokens);

    private:
        bool terminal(token_type);

        bool start();

        bool identifier();

        bool optional_where();

        bool lookahead_is(token_type type);

        bool end_of_tokens();

        bool where_conditions();

        bool where_condition();
    };
}

#endif
