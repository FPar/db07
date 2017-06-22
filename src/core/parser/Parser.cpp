#include <iostream>
#include <storage_engine/values/Varchar_value.h>
#include "Parser.h"
#include "parse_error.h"

using namespace std;
using namespace db07;

void Parser::parse(vector<Token> &tokens) {
    _lookahead = tokens.begin();
    _end = tokens.end();
    sql();
}

Query_data &Parser::query_data() {
    return _query_data;
}

void Parser::ensure_token_stream_not_empty() {
    if (_lookahead == _end) {
        throw runtime_error("Token stream ended unexpected");
    }
}

bool Parser::lookahead_is(token_type candidate) {
    ensure_token_stream_not_empty();
    return _lookahead->type() == candidate;
}

bool Parser::lookahead_is_one_of(std::vector<token_type> candidates) {
    ensure_token_stream_not_empty();
    token_type actual = _lookahead->type();
    for (token_type candidate : candidates) {
        if (actual == candidate) {
            return true;
        }
    }
    return false;
}

void Parser::throw_parse_error(std::vector<token_type> expected) {
    ensure_token_stream_not_empty();
    throw parse_error(expected, _lookahead->type());
}

void Parser::terminal(token_type expected) {
    ensure_token_stream_not_empty();
    token_type actual = _lookahead->type();
    if (actual == expected) {
        _lookahead++;
    } else {
        throw parse_error({expected}, actual);
    }
}

std::string Parser::terminal_string_value(token_type expected) {
    ensure_token_stream_not_empty();
    token_type actual = _lookahead->type();
    if (actual == expected) {
        return _lookahead++->string_value();
    } else {
        throw parse_error({expected}, actual);
    }
}

int Parser::terminal_int_value(token_type expected) {
    ensure_token_stream_not_empty();
    token_type actual = _lookahead->type();
    if (actual == expected) {
        return _lookahead++->int_value();
    } else {
        throw parse_error({expected}, actual);
    }
}

void Parser::sql() {
    select();
}

void Parser::select() {
    if (lookahead_is(token_type::SELECT)) {
        terminal(token_type::SELECT);
        _query_data.set_queryType(Query_type::SELECT);
        terminal(token_type::WHITESPACE);
        distinct();
    } else { throw_parse_error({token_type::SELECT}); }
}

void Parser::distinct() {
    if (lookahead_is(token_type::DISTINCT)) {
        terminal(token_type::DISTINCT);
        terminal(token_type::WHITESPACE);
        projection();
    } else if (lookahead_is_one_of({token_type::STAR, token_type::IDENTIFIER})) {
        projection();
    } else { throw_parse_error({token_type::DISTINCT, token_type::STAR, token_type::IDENTIFIER}); }
}

void Parser::projection() {
    if (lookahead_is(token_type::STAR)) {
        terminal(token_type::STAR);
        terminal(token_type::WHITESPACE);
        from();
    } else if (lookahead_is(token_type::IDENTIFIER)) {
        std::string column_name = terminal_string_value(token_type::IDENTIFIER);
        _query_data.getColumnNames().push_back(column_name);
        id_projection();
    } else { throw_parse_error({token_type::STAR, token_type::IDENTIFIER}); }
}

void Parser::id_projection() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        id_space_projection();
    } else if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        id_comma_projection();
    } else { throw_parse_error({token_type::WHITESPACE, token_type::COMMA}); }
}

void Parser::id_space_projection() {
    if (lookahead_is(token_type::FROM)) {
        from();
    } else if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        id_comma_projection();
    } else if (lookahead_is(token_type::AS)) {
        terminal(token_type::AS);
        terminal(token_type::WHITESPACE);
        std::string column_name = terminal_string_value(token_type::IDENTIFIER);
        _query_data.getColumnNames().push_back(column_name);
        id_as_projection();
    } else { throw_parse_error({token_type::FROM, token_type::COMMA, token_type::AS}); }
}

void Parser::id_comma_projection() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        std::string column_name = terminal_string_value(token_type::IDENTIFIER);
        _query_data.getColumnNames().push_back(column_name);
        id_projection();
    } else if (lookahead_is(token_type::IDENTIFIER)) {
        std::string column_name = terminal_string_value(token_type::IDENTIFIER);
        _query_data.getColumnNames().push_back(column_name);
        id_projection();
    } else { throw_parse_error({token_type::WHITESPACE, token_type::IDENTIFIER}); }
}

void Parser::id_as_projection() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        id_as_space_projection();
    } else if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        id_comma_projection();
    } else { throw_parse_error({token_type::WHITESPACE, token_type::COMMA}); }
}

void Parser::id_as_space_projection() {
    if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        id_comma_projection();
    } else if (lookahead_is(token_type::FROM)) {
        from();
    } else { throw_parse_error({token_type::COMMA, token_type::FROM}); }
}

void Parser::from() {
    if (lookahead_is(token_type::FROM)) {
        terminal(token_type::FROM);
        terminal(token_type::WHITESPACE);
        std::string table_name = terminal_string_value(token_type::IDENTIFIER);
        _query_data.getTableName().push_back(table_name);
        from_id();
    } else { throw_parse_error({token_type::FROM}); }
}

void Parser::from_id() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        from_id_space();
    } else if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        from_id_comma();
    } else if (lookahead_is_one_of({token_type::WHERE, token_type::ORDER, token_type::GROUP}) ||
               lookahead_is(token_type::END_OF_INPUT)) {
        after_from();
    } else {
        throw_parse_error(
                {token_type::WHITESPACE, token_type::COMMA, token_type::WHERE, token_type::ORDER, token_type::GROUP,
                 token_type::END_OF_INPUT});
    }
}

void Parser::from_id_space() {
    if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        from_id_comma();
    } else if (lookahead_is_one_of({token_type::WHERE, token_type::ORDER, token_type::GROUP}) ||
               lookahead_is(token_type::END_OF_INPUT)) {
        after_from();
    } else {
        throw_parse_error(
                {token_type::COMMA, token_type::WHERE, token_type::ORDER, token_type::GROUP, token_type::END_OF_INPUT});
    }
}

void Parser::from_id_comma() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        std::string table_name = terminal_string_value(token_type::IDENTIFIER);
        _query_data.getTableName().push_back(table_name);
        from_id();
    } else if (lookahead_is(token_type::IDENTIFIER)) {
        std::string table_name = terminal_string_value(token_type::IDENTIFIER);
        _query_data.getTableName().push_back(table_name);
        from_id();
    } else { throw_parse_error({token_type::WHITESPACE, token_type::IDENTIFIER}); }
}

void Parser::after_from() {
    if (lookahead_is(token_type::WHERE)) {
        where();
    } else if (lookahead_is(token_type::GROUP)) {
        group_by();
    } else if (lookahead_is(token_type::ORDER)) {
        order_by();
    } else if (lookahead_is(token_type::END_OF_INPUT)) {
        return;
    } else { throw_parse_error({token_type::WHERE, token_type::GROUP, token_type::ORDER, token_type::END_OF_INPUT}); }
}

void Parser::where() {
    if (lookahead_is(token_type::WHERE)) {
        terminal(token_type::WHERE);
        terminal(token_type::WHITESPACE);
        where_expr();
    } else { throw_parse_error({token_type::WHERE}); }
}

void Parser::where_expr() {
    if (lookahead_is(token_type::OPERATOR_NOT)) {
        terminal(token_type::OPERATOR_NOT);
        terminal(token_type::WHITESPACE);
        where_expr_pos();
    } else if (lookahead_is_one_of({token_type::LEFT_BRACKET, token_type::IDENTIFIER})) {
        where_expr_pos();
    } else { throw_parse_error({token_type::OPERATOR_NOT, token_type::LEFT_BRACKET, token_type::IDENTIFIER}); }
}

void Parser::where_expr_pos() {
    if (lookahead_is(token_type::LEFT_BRACKET)) {
        terminal(token_type::LEFT_BRACKET);
        where_expr_open();
    } else if (lookahead_is(token_type::IDENTIFIER)) {
        std::string column_name = terminal_string_value(token_type::IDENTIFIER);
        _query_condition.set_column(column_name);
        where_id();
        where_id_comp();
        where_id_comp_rval();
    } else { throw_parse_error({token_type::LEFT_BRACKET, token_type::IDENTIFIER}); }
}

void Parser::where_expr_open() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        where_expr();
        terminal(token_type::RIGHT_BRACKET);
    } else if (lookahead_is_one_of({token_type::OPERATOR_NOT, token_type::LEFT_BRACKET}) ||
               lookahead_is(token_type::IDENTIFIER)) {
        where_expr();
        terminal(token_type::RIGHT_BRACKET);
    } else {
        throw_parse_error(
                {token_type::WHITESPACE, token_type::OPERATOR_NOT, token_type::LEFT_BRACKET, token_type::IDENTIFIER});
    }
}

void Parser::where_id() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        where_comp();
    } else if (lookahead_is_one_of({token_type::OPERATOR_EQ, token_type::OPERATOR_LE}) ||
               lookahead_is_one_of({token_type::OPERATOR_LT, token_type::OPERATOR_GT}) ||
               lookahead_is(token_type::OPERATOR_GE)) {
        where_comp();
    } else {
        throw_parse_error(
                {token_type::WHITESPACE, token_type::OPERATOR_EQ, token_type::OPERATOR_LE, token_type::OPERATOR_LT,
                 token_type::OPERATOR_GT, token_type::OPERATOR_GE});
    }
}

void Parser::where_comp() {
    if (lookahead_is(token_type::OPERATOR_EQ)) {
        terminal(token_type::OPERATOR_EQ);
        _query_condition.set_operation("=");
    } else if (lookahead_is(token_type::OPERATOR_LE)) {
        terminal(token_type::OPERATOR_LE);
        _query_condition.set_operation("<=");
    } else if (lookahead_is(token_type::OPERATOR_LT)) {
        terminal(token_type::OPERATOR_LT);
        _query_condition.set_operation("<");
    } else if (lookahead_is(token_type::OPERATOR_GT)) {
        terminal(token_type::OPERATOR_GT);
        _query_condition.set_operation(">");
    } else if (lookahead_is(token_type::OPERATOR_GE)) {
        terminal(token_type::OPERATOR_GE);
        _query_condition.set_operation(">=");
    } else {
        throw_parse_error(
                {token_type::OPERATOR_EQ, token_type::OPERATOR_LE, token_type::OPERATOR_LT, token_type::OPERATOR_GT,
                 token_type::OPERATOR_GE});
    }
}

void Parser::where_id_comp() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        where_rval();
    } else if (lookahead_is_one_of({token_type::IDENTIFIER, token_type::STRING_LITERAL}) ||
               lookahead_is(token_type::INTEGER_LITERAL)) {
        where_rval();
    } else {
        throw_parse_error({token_type::WHITESPACE, token_type::IDENTIFIER, token_type::STRING_LITERAL,
                           token_type::INTEGER_LITERAL});
    }
}

void Parser::where_rval() {
    if (lookahead_is(token_type::IDENTIFIER)) {
        terminal(token_type::IDENTIFIER);
    } else if (lookahead_is(token_type::STRING_LITERAL)) {
        std::string rval = terminal_string_value(token_type::STRING_LITERAL);
        Varchar_value r_value(rval);
        _query_condition.set_value(&r_value);
        _query_data.getConditions().push_back(_query_condition);
    } else if (lookahead_is(token_type::INTEGER_LITERAL)) {
        int rval = terminal_int_value(token_type::INTEGER_LITERAL);
        Int_value r_value(rval);
        _query_condition.set_value(&r_value);
        _query_data.getConditions().push_back(_query_condition);
    } else { throw_parse_error({token_type::IDENTIFIER, token_type::STRING_LITERAL, token_type::INTEGER_LITERAL}); }
}

void Parser::where_id_comp_rval() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        where_comp_space();
    } else if (lookahead_is_one_of({token_type::RIGHT_BRACKET, token_type::END_OF_INPUT})) {
        return;
    } else { throw_parse_error({token_type::WHITESPACE, token_type::RIGHT_BRACKET, token_type::END_OF_INPUT}); }
}

void Parser::where_comp_space() {
    if (lookahead_is(token_type::OPERATOR_AND)) {
        terminal(token_type::OPERATOR_AND);
        _query_data.get_booleanOperations().push_back("and");
        terminal(token_type::WHITESPACE);
        where_expr();
    } else if (lookahead_is(token_type::OPERATOR_OR)) {
        terminal(token_type::OPERATOR_OR);
        _query_data.get_booleanOperations().push_back("or");
        terminal(token_type::WHITESPACE);
        where_expr();
    } else if (lookahead_is_one_of({token_type::RIGHT_BRACKET, token_type::END_OF_INPUT})) {
        return;
    } else {
        throw_parse_error(
                {token_type::OPERATOR_AND, token_type::OPERATOR_OR, token_type::WHITESPACE, token_type::RIGHT_BRACKET,
                 token_type::END_OF_INPUT});
    }
}

void Parser::group_by() {
    if (lookahead_is(token_type::GROUP)) {
        terminal(token_type::GROUP);
        terminal(token_type::WHITESPACE);
        terminal(token_type::BY);
        terminal(token_type::WHITESPACE);
        terminal(token_type::IDENTIFIER);
        group_by_id();
    } else { throw_parse_error({token_type::GROUP}); }
}

void Parser::group_by_id() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        group_by_id_space();
    } else if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        group_by_id_comma();
    } else { throw_parse_error({token_type::WHITESPACE, token_type::COMMA}); }
}

void Parser::group_by_id_space() {
    if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        group_by_id_comma();
    } else if (lookahead_is(token_type::ORDER)) {
        order_by();
    } else if (lookahead_is(token_type::END_OF_INPUT)) {
        return;
    } else { throw_parse_error({token_type::COMMA, token_type::ORDER, token_type::END_OF_INPUT}); }
}

void Parser::group_by_id_comma() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        terminal(token_type::IDENTIFIER);
        group_by_id();
    } else if (lookahead_is(token_type::IDENTIFIER)) {
        terminal(token_type::IDENTIFIER);
        group_by_id();
    } else { throw_parse_error({token_type::WHITESPACE, token_type::IDENTIFIER}); }
}

void Parser::order_by() {
    if (lookahead_is(token_type::ORDER)) {
        terminal(token_type::ORDER);
        terminal(token_type::WHITESPACE);
        terminal(token_type::BY);
        terminal(token_type::WHITESPACE);
        terminal(token_type::IDENTIFIER);
        order_by_id();
    } else { throw_parse_error({token_type::ORDER}); }
}

void Parser::order_by_id() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        order_by_id_space();
    } else if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        order_by_id_comma();
    } else if (lookahead_is(token_type::END_OF_INPUT)) {
        return;
    } else { throw_parse_error({token_type::WHITESPACE, token_type::COMMA, token_type::END_OF_INPUT}); }
}

void Parser::order_by_id_space() {
    if (lookahead_is(token_type::ASC)) {
        terminal(token_type::ASC);
        order_by_id_ascdesc();
    } else if (lookahead_is(token_type::DESC)) {
        terminal(token_type::DESC);
        order_by_id_ascdesc();
    } else if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        order_by_id_comma();
    } else if (lookahead_is(token_type::END_OF_INPUT)) {
        return;
    } else { throw_parse_error({token_type::ASC, token_type::DESC, token_type::COMMA, token_type::END_OF_INPUT}); }
}

void Parser::order_by_id_ascdesc() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        order_by_id_ascdesc_space();
    } else if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        order_by_id_comma();
    } else if (lookahead_is(token_type::END_OF_INPUT)) {
        return;
    } else { throw_parse_error({token_type::WHITESPACE, token_type::COMMA, token_type::END_OF_INPUT}); }
}

void Parser::order_by_id_ascdesc_space() {
    if (lookahead_is(token_type::COMMA)) {
        terminal(token_type::COMMA);
        order_by_id_comma();
    } else if (lookahead_is(token_type::END_OF_INPUT)) {
        return;
    } else { throw_parse_error({token_type::COMMA, token_type::END_OF_INPUT}); }
}

void Parser::order_by_id_comma() {
    if (lookahead_is(token_type::WHITESPACE)) {
        terminal(token_type::WHITESPACE);
        terminal(token_type::IDENTIFIER);
        order_by_id();
    } else if (lookahead_is(token_type::IDENTIFIER)) {
        terminal(token_type::IDENTIFIER);
        order_by_id();
    } else { throw_parse_error({token_type::WHITESPACE, token_type::IDENTIFIER}); }
}
