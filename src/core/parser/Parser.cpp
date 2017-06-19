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
    throw runtime_error("Unknown token.");
}

bool Parser::parse_error(vector<token_type> expected, bool or_eof = false) {
    cout << "Syntax error: Expected ";
    if (expected.size() > 1) {
        cout << "one of ";
        for (token_type type : expected) {
            cout << token_to_string(type) << ", ";
        }
    } else {
        cout << token_to_string(expected.front()) << " ";
    }
    if (or_eof) {
        cout << "or EOF ";
    }
    cout << "but ";
    if (!or_eof && _lookahead == _end) {
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
        return terminal(token_type::AS) && terminal(token_type::WHITESPACE) && terminal(token_type::IDENTIFIER) && id_as_projection();
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
        return terminal(token_type::FROM) && terminal(token_type::WHITESPACE) && terminal(token_type::IDENTIFIER) && from_id();
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
    if (lookahead_is_eof()) {
        return true;
    }
    return parse_error({token_type::WHITESPACE, token_type::COMMA}, true);
}

bool Parser::from_id_space() {
    if (lookahead_is(token_type::COMMA)) {
        return terminal(token_type::COMMA) && from_id_comma();
    }
    if (lookahead_is_eof()) {
        return true;
    }
    return parse_error({token_type::COMMA}, true);
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

bool Parser::where() {
    return false;
}

bool Parser::selection() {
    return false;
}

bool Parser::condition() {
    return false;
}

bool Parser::comp_op() {
    return false;
}

bool Parser::condition_op() {
    return false;
}

bool Parser::condition_rval() {
    return false;
}

bool Parser::condition_end() {
    return false;
}
