#include <iostream>
#include "catch.h"
#include "parser/Lexer.h"

namespace db07 {
    TEST_CASE("", "") {
        Lexer lexer;
        std::string input = "students WHERE firstname = 'Alex' AND lastname = 'aa'";
        auto tokens = lexer.tokenize(input);
        for (auto token = tokens.begin(); token != tokens.end(); token++) {
            switch (token->type()) {
                case token_type::WHITESPACE:
                std::cout << "WHITESPACE";
                    break;
                case token_type::LEFT_BRACKET:
                    std::cout << "LEFT_BRACKET";
                    break;
                case token_type::RIGHT_BRACKET:
                    std::cout << "RIGHT_BRACKET";
                    break;
                case token_type::OPERATOR_EQ:
                    std::cout << "OPERATOR_EQ";
                    break;
                case token_type::OPERATOR_NEQ:
                    std::cout << "OPERATOR_NEQ";
                    break;
                case token_type::OPERATOR_LT:
                    std::cout << "OPERATOR_LT";
                    break;
                case token_type::OPERATOR_LE:
                    std::cout << "OPERATOR_LE";
                    break;
                case token_type::OPERATOR_GE:
                    std::cout << "OPERATOR_GE";
                    break;
                case token_type::OPERATOR_GT:
                    std::cout << "OPERATOR_GT";
                    break;
                case token_type::OPERATOR_AND:
                    std::cout << "OPERATOR_AND";
                    break;
                case token_type::OPERATOR_OR:
                    std::cout << "OPERATOR_OR";
                    break;
                case token_type::OPERATOR_NOT:
                    std::cout << "OPERATOR_NOT";
                    break;
                case token_type::OPERATOR_IN:
                    std::cout << "OPERATOR_IN";
                    break;
                case token_type::KEYWORD_SELECT:
                    std::cout << "KEYWORD_SELECT";
                    break;
                case token_type::KEYWORD_DISTINCT:
                    std::cout << "KEYWORD_DISTINCT";
                    break;
                case token_type::KEYWORD_FROM:
                    std::cout << "KEYWORD_FROM";
                    break;
                case token_type::KEYWORD_WHERE:
                    std::cout << "KEYWORD_WHERE";
                    break;
                case token_type::INTEGER_LITERAL:
                    std::cout << "INTEGER_LITERAL(" << token->int_value() << ")";
                    break;
                case token_type::STRING_LITERAL:
                    std::cout << "STRING_LITERAL(" << token->string_value() << ")";
                    break;
                case token_type::IDENTIFIER:
                    std::cout << "IDENTIFIER(" << token->string_value() << ")";
                    break;
                case token_type::UNRECOGNIZED:
                    std::cout << "UNRECOGNIZED(" << token->string_value() << ")";
                    break;
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}