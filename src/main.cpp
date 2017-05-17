#include <iostream>
#include "parser/lexer.h"
#include "storage_engine/Catalog.h"

int main(int argc, char **argv) {
    db07::Lexer lexer;

    std::cout << "db07 Interactive mode\nEnter query or 'q' to quit.\ndb07 > ";
    std::string input;
    std::getline(std::cin, input);
    bool quited = input.compare("q") == 0;
    while (!quited) {
        std::list<db07::Token> tokens = lexer.tokenize(input);
        if (tokens.back().type() == db07::token_type::UNRECOGNIZED) {
            const std::string &unrecognized_token_string = tokens.back().string_value();
            std::cout << "Unrecognized token '"
                      << unrecognized_token_string
                      << "'\n\n";
        } else {
            for (std::list<db07::Token>::const_iterator token = tokens.begin();
                 token != tokens.end();
                 token++) {
                switch (token->type()) {
                    case db07::token_type::OPERATOR_EQ:
                        std::cout << "EQUAL ";
                        break;
                    case db07::token_type::OPERATOR_NEQ:
                        std::cout << "NOT_EQUAL ";
                        break;
                    case db07::token_type::OPERATOR_LT:
                        std::cout << "LESS_THAN ";
                        break;
                    case db07::token_type::OPERATOR_LE:
                        std::cout << "LESS_OR_EQUAL ";
                        break;
                    case db07::token_type::OPERATOR_GE:
                        std::cout << "GREATER_OR_EQUAL ";
                        break;
                    case db07::token_type::OPERATOR_GT:
                        std::cout << "GREATER_THAN ";
                        break;
                    case db07::token_type::OPERATOR_AND:
                        std::cout << "AND ";
                        break;
                    case db07::token_type::OPERATOR_OR:
                        std::cout << "OR ";
                        break;
                    case db07::token_type::OPERATOR_NOT:
                        std::cout << "NOT ";
                        break;
                    case db07::token_type::OPERATOR_IN:
                        std::cout << "IN ";
                        break;
                    case db07::token_type::KEYWORD_SELECT:
                        std::cout << "SELECT ";
                        break;
                    case db07::token_type::KEYWORD_DISTINCT:
                        std::cout << "DISTINCT ";
                        break;
                    case db07::token_type::KEYWORD_FROM:
                        std::cout << "FROM ";
                        break;
                    case db07::token_type::KEYWORD_WHERE:
                        std::cout << "WHERE ";
                        break;
                    case db07::token_type::INTEGER:
                        std::cout << "INTEGER[" << token->int_value() << "] ";
                        break;
                    case db07::token_type::LITERAL:
                        std::cout << "LITERAL[" << token->string_value() << "] ";
                        break;
                    case db07::token_type::IDENTIFIER:
                        std::cout << "IDENTIFIER[" << token->string_value() << "] ";
                        break;
                    default:
                        break;
                }
            }
            std::cout << "\n\n";
        }

        std::cout << "db07 > ";
        std::getline(std::cin, input);
        quited = input.compare("q") == 0;
    }
    return 0;
}
