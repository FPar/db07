#include <iostream>
#include "Parser.h"

using namespace std;
using namespace db07;

void Parser::parse(vector<Token> &tokens) {
    _lookahead = tokens.begin();
    _end = tokens.end();
    if (sql()) {
        cout << "OK" << endl;
    }
}

bool Parser::sql() {
    return select();
}

bool Parser::lookahead_is_eof() {
    return _lookahead == _end;
}

bool Parser::lookahead_is(token_type type) {
    return !lookahead_is_eof() && _lookahead->type() == type;
}

string Parser::token_to_string(token_type type) {
    switch (type) {
        case token_type::WHITESPACE:
            return "WHITESPACE";
        case token_type::LEFT_BRACKET:
            return "LEFT_BRACKET";
        case token_type::RIGHT_BRACKET:
            return "RIGHT_BRACKET";
        case token_type::OPERATOR_EQ:
            return "OPERATOR_EQ";
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
        case token_type::SELECT:
            return "SELECT";
        case token_type::DISTINCT:
            return "DISTINCT";
        case token_type::FROM:
            return "FROM";
        case token_type::WHERE:
            return "WHERE";
        case token_type::GROUP:
            return "GROUP";
        case token_type::ORDER:
            return "ORDER";
        case token_type::BY:
            return "BY";
        case token_type::ASC:
            return "ASC";
        case token_type::DESC:
            return "DESC";
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
    throw runtime_error("Unknown token.");
}

bool Parser::parse_error(vector<token_type> expected, bool eof_allowed = false) {
    cout << "Syntax error: Expected ";
    if (expected.size() > 1) {
        cout << "one of ";
        for (token_type type : expected) {
            cout << token_to_string(type) << ", ";
        }
    } else {
        cout << token_to_string(expected.front()) << " ";
    }
    if (eof_allowed) {
        cout << "or EOF ";
    }
    cout << "but ";
    if (!eof_allowed && _lookahead == _end) {
        cout << "reached end of input";
    } else {
        cout << "found " << token_to_string(_lookahead->type());
    }
    cout << endl;
    return false;
}

bool Parser::terminal(token_type type) {
    if (lookahead_is(type)) {
        _lookahead++;
        return true;
    }
    return parse_error({type});
}

bool Parser::select() {
    if (lookahead_is(token_type::SELECT)) {
        return terminal(token_type::SELECT) && terminal(token_type::WHITESPACE) && distinct();
    }
    return parse_error({token_type::SELECT});
}

bool Parser::distinct() {
    if (lookahead_is(token_type::DISTINCT)) {
        return terminal(token_type::DISTINCT) && terminal(token_type::WHITESPACE) && projection();
    }
    if (lookahead_is(token_type::STAR) || lookahead_is(token_type::IDENTIFIER)) {
        return projection();
    }
    return parse_error({token_type::DISTINCT, token_type::STAR, token_type::IDENTIFIER});
}

bool Parser::projection() {
    if (lookahead_is(token_type::STAR)) {
        return terminal(token_type::STAR) && terminal(token_type::WHITESPACE) && from();
    }
    if (lookahead_is(token_type::IDENTIFIER)) {
        return terminal(token_type::IDENTIFIER) && id_projection();
    }
    return parse_error({token_type::STAR, token_type::IDENTIFIER});
}

bool Parser::id_projection() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && id_space_projection();
    }
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && id_comma_projection();
    }
    return parse_error({token_type::WHITESPACE, token_type::COMMA});
}

bool Parser::id_space_projection() {
    if (lookahead_is(token_type::FROM)) {
        return from();
    }
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && id_comma_projection();
    }
    if (lookahead_is(token_type::AS)) {
        return terminal(token_type::AS) && terminal(token_type::WHITESPACE) && terminal(token_type::IDENTIFIER) &&
               id_as_projection();
    }
    return parse_error({token_type::FROM, token_type::COMMA, token_type::AS});
}

bool Parser::id_comma_projection() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && terminal(token_type::IDENTIFIER) && id_projection();
    }
    if (lookahead_is(token_type::IDENTIFIER)) {
        return terminal(token_type::IDENTIFIER) && id_projection();
    }
    return parse_error({token_type::WHITESPACE, token_type::IDENTIFIER});
}

bool Parser::id_as_projection() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && id_as_space_projection();
    }
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && id_comma_projection();
    }
    return parse_error({token_type::WHITESPACE, token_type::COMMA});
}

bool Parser::id_as_space_projection() {
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && id_comma_projection();
    }
    if (lookahead_is(token_type::FROM)) {
        return from();
    }
    return parse_error({token_type::COMMA, token_type::FROM});
}

bool Parser::from() {
    if (lookahead_is(token_type::FROM)) {
        return terminal(token_type::FROM) && terminal(token_type::WHITESPACE) && terminal(token_type::IDENTIFIER) &&
               from_id();
    }
    return parse_error({token_type::FROM});
}

bool Parser::from_id() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && from_id_space();
    }
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && from_id_comma();
    }
    if (lookahead_is(token_type::WHERE) || lookahead_is(token_type::ORDER) || lookahead_is(token_type::GROUP) ||
        lookahead_is_eof()) {
        return after_from();
    }
    return parse_error(
            {token_type::WHITESPACE, token_type::COMMA, token_type::WHERE, token_type::ORDER, token_type::GROUP}, true);
}

bool Parser::from_id_space() {
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && from_id_comma();
    }
    if (lookahead_is(token_type::WHERE) || lookahead_is(token_type::ORDER) || lookahead_is(token_type::GROUP) ||
        lookahead_is_eof()) {
        return after_from();
    }
    return parse_error({token_type::COMMA, token_type::WHERE, token_type::ORDER, token_type::GROUP}, true);
}

bool Parser::from_id_comma() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && terminal(token_type::IDENTIFIER) && from_id();
    }
    if (lookahead_is(token_type::IDENTIFIER)) {
        return terminal(token_type::IDENTIFIER) && from_id();
    }
    return parse_error({token_type::WHITESPACE, token_type::IDENTIFIER});
}

bool Parser::after_from() {
    if (lookahead_is(token_type::WHERE)) {
        return where();
    }
    if (lookahead_is(token_type::GROUP)) {
        return group_by();
    }
    if (lookahead_is(token_type::ORDER)) {
        return order_by();
    }
    if (lookahead_is_eof()) {
        return true;
    }
    return parse_error({token_type::WHERE, token_type::GROUP, token_type::ORDER}, true);
}

bool Parser::where() {
    if (lookahead_is(token_type::WHERE)) {
        return terminal(token_type::WHERE) && terminal(token_type::WHITESPACE) && where_expr();
    }
    return parse_error({token_type::WHERE});
}

bool Parser::where_expr() {
    if (lookahead_is(token_type::OPERATOR_NOT)) {
        return terminal(token_type::OPERATOR_NOT) && terminal(token_type::WHITESPACE) && where_expr_pos();
    }
    if (lookahead_is(token_type::LEFT_BRACKET) || lookahead_is(token_type::IDENTIFIER)) {
        return where_expr_pos();
    }
    return parse_error({token_type::OPERATOR_NOT, token_type::LEFT_BRACKET, token_type::IDENTIFIER});
}

bool Parser::where_expr_pos() {
    if (lookahead_is(token_type::LEFT_BRACKET)) {
        return terminal(token_type::LEFT_BRACKET) && where_expr_open();
    }
    if (lookahead_is(token_type::IDENTIFIER)) {
        return terminal(token_type::IDENTIFIER) && where_id() && where_id_comp() && where_id_comp_rval();
    }
    return parse_error({token_type::LEFT_BRACKET, token_type::IDENTIFIER});
}

bool Parser::where_expr_open() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && where_expr() && terminal(token_type::RIGHT_BRACKET);
    }
    if (lookahead_is(token_type::OPERATOR_NOT) || lookahead_is(token_type::LEFT_BRACKET) ||
        lookahead_is(token_type::IDENTIFIER)) {
        return where_expr() && terminal(token_type::RIGHT_BRACKET);
    }
    return parse_error(
            {token_type::WHITESPACE, token_type::OPERATOR_NOT, token_type::LEFT_BRACKET, token_type::IDENTIFIER});
}

bool Parser::where_id() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && where_comp();
    }
    if (lookahead_is(token_type::OPERATOR_EQ) || lookahead_is(token_type::OPERATOR_LE) ||
        lookahead_is(token_type::OPERATOR_LT) || lookahead_is(token_type::OPERATOR_GT) ||
        lookahead_is(token_type::OPERATOR_GE)) {
        return where_comp();
    }
    return parse_error(
            {token_type::WHITESPACE, token_type::OPERATOR_EQ, token_type::OPERATOR_LE, token_type::OPERATOR_LT,
             token_type::OPERATOR_GT, token_type::OPERATOR_GE});
}

bool Parser::where_comp() {
    if (lookahead_is(token_type::OPERATOR_EQ)) {
        return terminal(token_type::OPERATOR_EQ);
    }
    if (lookahead_is(token_type::OPERATOR_LE)) {
        return terminal(token_type::OPERATOR_LE);
    }
    if (lookahead_is(token_type::OPERATOR_LT)) {
        return terminal(token_type::OPERATOR_LT);
    }
    if (lookahead_is(token_type::OPERATOR_GT)) {
        return terminal(token_type::OPERATOR_GT);
    }
    if (lookahead_is(token_type::OPERATOR_GE)) {
        return terminal(token_type::OPERATOR_GE);
    }
    return parse_error(
            {token_type::OPERATOR_EQ, token_type::OPERATOR_LE, token_type::OPERATOR_LT, token_type::OPERATOR_GT,
             token_type::OPERATOR_GE});
}

bool Parser::where_id_comp() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && where_rval();
    }
    if (lookahead_is(token_type::IDENTIFIER) || lookahead_is(token_type::STRING_LITERAL) ||
        lookahead_is(token_type::INTEGER_LITERAL)) {
        return where_rval();
    }
    return parse_error(
            {token_type::WHITESPACE, token_type::IDENTIFIER, token_type::STRING_LITERAL, token_type::INTEGER_LITERAL});
}

bool Parser::where_rval() {
    if (lookahead_is(token_type::IDENTIFIER)) {
        return terminal(token_type::IDENTIFIER);
    }
    if (lookahead_is(token_type::STRING_LITERAL)) {
        return terminal(token_type::STRING_LITERAL);
    }
    if (lookahead_is(token_type::INTEGER_LITERAL)) {
        return terminal(token_type::INTEGER_LITERAL);
    }
    return parse_error({token_type::IDENTIFIER, token_type::STRING_LITERAL, token_type::INTEGER_LITERAL});
}

bool Parser::where_id_comp_rval() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && where_comp_space();
    }
    if (lookahead_is(token_type::RIGHT_BRACKET) || lookahead_is_eof()) {
        return true;
    }
    return parse_error({token_type::WHITESPACE, token_type::RIGHT_BRACKET}, true);
}

bool Parser::where_comp_space() {
    if (lookahead_is(token_type::OPERATOR_AND)) {
        return terminal(token_type::OPERATOR_AND) && terminal(token_type::WHITESPACE) && where_expr();
    }
    if (lookahead_is(token_type::OPERATOR_OR)) {
        return terminal(token_type::OPERATOR_OR) && terminal(token_type::WHITESPACE) && where_expr();
    }
    if (lookahead_is(token_type::RIGHT_BRACKET) || lookahead_is_eof()) {
        return true;
    }
    return parse_error(
            {token_type::OPERATOR_AND, token_type::OPERATOR_OR, token_type::WHITESPACE, token_type::RIGHT_BRACKET},
            true);
}

bool Parser::group_by() {
    if (lookahead_is(token_type::GROUP)) {
        return terminal(token_type::GROUP) && terminal(token_type::WHITESPACE) && terminal(token_type::BY) &&
               terminal(token_type::WHITESPACE) && terminal(token_type::IDENTIFIER) && group_by_id();
    }
    return parse_error({token_type::GROUP});
}

bool Parser::group_by_id() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && group_by_id_space();
    }
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && group_by_id_comma();
    }
    return parse_error({token_type::WHITESPACE, token_type::COMMA});
}

bool Parser::group_by_id_space() {
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && group_by_id_comma();
    }
    if (lookahead_is(token_type::ORDER)) {
        return order_by();
    }
    if (lookahead_is_eof()) {
        return true;
    }
    return parse_error({token_type::COMMA, token_type::ORDER}, true);
}

bool Parser::group_by_id_comma() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && terminal(token_type::IDENTIFIER) && group_by_id();
    }
    if (lookahead_is(token_type::IDENTIFIER)) {
        return terminal(token_type::IDENTIFIER) && group_by_id();
    }
    return parse_error({token_type::WHITESPACE, token_type::IDENTIFIER});
}

bool Parser::order_by() {
    if (lookahead_is(token_type::ORDER)) {
        return terminal(token_type::ORDER) && terminal(token_type::WHITESPACE) && terminal(token_type::BY) &&
               terminal(token_type::WHITESPACE) && terminal(token_type::IDENTIFIER) && order_by_id();
    }
    return parse_error({token_type::ORDER});
}

bool Parser::order_by_id() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && order_by_id_space();
    }
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && order_by_id_comma();
    }
    if (lookahead_is_eof()) {
        return true;
    }
    return parse_error({token_type::WHITESPACE, token_type::COMMA}, true);
}

bool Parser::order_by_id_space() {
    if (lookahead_is(token_type::ASC)) {
        return terminal(token_type::ASC) && order_by_id_ascdesc();
    }
    if (lookahead_is(token_type::DESC)) {
        return terminal(token_type::DESC) && order_by_id_ascdesc();
    }
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && order_by_id_comma();
    }
    if (lookahead_is_eof()) {
        return true;
    }
    return parse_error({token_type::ASC, token_type::DESC, token_type::COMMA}, true);
}

bool Parser::order_by_id_ascdesc() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && order_by_id_ascdesc_space();
    }
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && order_by_id_comma();
    }
    if (lookahead_is_eof()) {
        return true;
    }
    return parse_error({token_type::WHITESPACE, token_type::COMMA}, true);
}

bool Parser::order_by_id_ascdesc_space() {
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && order_by_id_comma();
    }
    if (lookahead_is_eof()) {
        return true;
    }
    return parse_error({token_type::COMMA}, true);
}

bool Parser::order_by_id_comma() {
    if (lookahead_is(token_type::WHITESPACE)) {
        return terminal(token_type::WHITESPACE) && terminal(token_type::IDENTIFIER) && order_by_id();
    }
    if (lookahead_is(token_type::IDENTIFIER)) {
        return terminal(token_type::IDENTIFIER) && order_by_id();
    }
    return parse_error({token_type::WHITESPACE, token_type::IDENTIFIER});
}
