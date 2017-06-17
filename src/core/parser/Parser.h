#ifndef DB07_PARSER_H
#define DB07_PARSER_H

#include <iostream>
#include <list>
#include "Token.h"

namespace db07 {
    class Parser {
    private:
        std::list<Token>::const_iterator _lookahead;
        std::list<Token>::const_iterator _end;

    public:
        void parse(std::list<Token> &tokens) {
            _lookahead = tokens.begin();
            _end = tokens.end();
            if (sql()) {
                std::cout << "OK" << std::endl;
            }
        }

    private:
        bool sql() {
            return select();
        }

        bool lookahead_is(token_type type) {
            return _lookahead == _end ? false
                                      : _lookahead->type() == type;
        }

        std::string token_to_string(token_type type) {
            switch (type) {
                case token_type::WHITESPACE:
                    return "WHITESPACE";
                case token_type::LEFT_BRACKET:
                    return "LEFT_BRACKET";
                case token_type::RIGHT_BRACKET:
                    return "RIGHT_BRACKET";
                case token_type::OPERATOR_EQ:
                    return "OPERATOR_EQ";
                case token_type::OPERATOR_NEQ:
                    return "OPERATOR_NEQ";
                case token_type::OPERATOR_LT:
                    return "OPERATOR_LT";
                case token_type::OPERATOR_LE:
                    return "OPERATOR_LE";
                case token_type::OPERATOR_GE:
                    return "OPERATOR_GE";
                case token_type::OPERATOR_GT:
                    return "OPERATOR_GT";
                case token_type::OPERATOR_AND:
                    return "OPERATOR_AND";
                case token_type::OPERATOR_OR:
                    return "OPERATOR_OR";
                case token_type::OPERATOR_NOT:
                    return "OPERATOR_NOT";
                case token_type::OPERATOR_IN:
                    return "OPERATOR_IN";
                case token_type::SELECT:
                    return "SELECT";
                case token_type::DISTINCT:
                    return "DISTINCT";
                case token_type::FROM:
                    return "FROM";
                case token_type::WHERE:
                    return "WHERE";
                case token_type::INTEGER_LITERAL:
                    return "INTEGER_LITERAL";
                case token_type::STRING_LITERAL:
                    return "STRING_LITERAL";
                case token_type::IDENTIFIER:
                    return "IDENTIFIER";
                case token_type::UNRECOGNIZED:
                    return "UNRECOGNIZED";
                case token_type::STAR:
                    return "STAR";
                case token_type::COMMA:
                    return "COMMA";
                case token_type::AS:
                    return "AS";
            }
        }

        bool parse_error(std::list<token_type> expected) {
            std::cout << "Syntax error: Expected ";
            if (expected.size() > 1) {
                std::cout << "one of ";
                for (token_type type : expected) {
                    std::cout << token_to_string(type) << ", ";
                }
            } else {
                std::cout << token_to_string(expected.front()) << " ";
            }
            std::cout << "but ";
            if (_lookahead == _end) {
                std::cout << "reached end of input";
            } else {
                std::cout << "found " << token_to_string(_lookahead->type());
            }
            std::cout << std::endl;
            return false;
        }

        bool terminal(token_type type) {
            if (lookahead_is(type)) {
                _lookahead++;
                return true;
            }
            return parse_error({type});
        }

        bool select() {
            if (lookahead_is(token_type::SELECT)) {
                return terminal(token_type::SELECT)
                       && terminal(token_type::WHITESPACE)
                       && optional_distinct()
                       && projection()
                       && terminal(token_type::FROM)
                       && terminal(token_type::WHITESPACE)
                       && terminal(token_type::IDENTIFIER);
            }
            return parse_error({token_type::SELECT});
        }

        bool optional_distinct() {
            if (lookahead_is(token_type::DISTINCT)) {
                return terminal(token_type::DISTINCT)
                       && terminal(token_type::WHITESPACE);
            }
            return true;
        }

        bool projection() {
            if (lookahead_is(token_type::STAR)) {
                return terminal(token_type::STAR)
                       && terminal(token_type::WHITESPACE);
            }
            if (lookahead_is(token_type::IDENTIFIER)) {
                return projection_list();
            }
            return parse_error({token_type::STAR, token_type ::IDENTIFIER});
        }

        bool projection_list() {
            if (lookahead_is(token_type::IDENTIFIER)) {
                return terminal(token_type::IDENTIFIER)
                       && optional_renaming()
                       && optional_projection_list();
            }
            return parse_error({token_type::IDENTIFIER});
        }

        bool optional_renaming() {
            if (lookahead_is(token_type::AS)) {
                return terminal(token_type::AS)
                       && terminal(token_type::IDENTIFIER);
            }
            return true;
        }

        bool optional_projection_list() {
            if (lookahead_is(token_type::COMMA)) {
                return terminal(token_type::COMMA)
                       && projection_list();
            }
            return true;
        }
    };
}

#endif
