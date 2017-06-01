#include <iostream>
#include "Parser.h"

namespace db07 {
    void Parser::parse(std::list<Token> &tokens) {
        lookahead = tokens.begin();
        end = tokens.end();
        if (start()) {
            std::cout << "OK\n";
        }
    }

    bool Parser::start() {
        if (lookahead_is(token_type::KEYWORD_SELECT)) {
            return terminal(token_type::KEYWORD_SELECT)
                   && terminal(token_type::KEYWORD_FROM)
                   && identifier()
                   && optional_where()
                   && end_of_tokens();
        }
        return false;
    }

    bool Parser::identifier() {
        if (lookahead_is(token_type::IDENTIFIER)) {
            return terminal(token_type::IDENTIFIER);
        }
        std::cerr << "Expected IDENTIFIER\n";
        return false;
    }

    bool Parser::optional_where() {
        if (lookahead_is(token_type::KEYWORD_WHERE)) {
            return terminal(token_type::KEYWORD_WHERE)
                    && where_conditions();
        }
        return true;
    }

    bool Parser::where_conditions() {
        if (lookahead_is(token_type::IDENTIFIER)) {
            return terminal(token_type::IDENTIFIER);
        }
        std::cerr << "Expected IDENTIFIER\n";
        return false;
    }

    bool Parser::terminal(token_type expected) {
        if (!lookahead_is(expected)) {
            std::cerr << "Expected\n";
            return false;
        }
        // TODO process terminal
        lookahead++;
        return true;
    }

    bool Parser::lookahead_is(token_type type) {
        return lookahead == end
               ? false
               : lookahead->type() == type;
    }

    bool Parser::end_of_tokens() {
        if (lookahead != end) {
            std::cerr << "Expected no more tokens\n";
            return false;
        }
        return true;
    }
}
