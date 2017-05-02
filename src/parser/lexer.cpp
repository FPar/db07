#include "lexer.h"

namespace db07 {
    std::list<Token> Lexer::tokenize(std::string &input) {
        std::list<Token> tokens;
        std::string token_string;
        for (std::string::iterator input_iterator = input.begin();
             input_iterator < input.end();
             input_iterator++) {
            char chr = *input_iterator;
            if (is_delimiter(chr)) {
                TokenType token_type = recognize(token_string);
                Token token = evaluate(token_type, token_string);
                tokens.push_back(token);
                if (token_type == TokenType::UNRECOGNIZED) {
                    return tokens;
                }
                token_string = {};
            } else {
                token_string += chr;
            }
        }
        TokenType token_type = recognize(token_string);
        Token token = evaluate(token_type, token_string);
        tokens.push_back(token);
        return tokens;
    }

    bool Lexer::is_delimiter(char chr) {
        return chr == ' ';
    }

    TokenType Lexer::recognize(std::string &token_string) {
        static const std::regex REGEX_INTEGER("[0-9]+", std::regex_constants::icase);
        static const std::regex REGEX_LITERAL("\'.*\'", std::regex_constants::icase);
        static const std::regex REGEX_IDENTIFIER("[a-z][a-z0-9_]*", std::regex_constants::icase);

        if (token_string.compare("==") == 0) {
            return TokenType::OPERATOR_EQ;
        } else if (token_string.compare("!=") == 0) {
            return TokenType::OPERATOR_NEQ;
        } else if (token_string.compare("SELECT") == 0) {
            return TokenType::KEYWORD_SELECT;
        } else if (token_string.compare("FROM") == 0) {
            return TokenType::KEYWORD_FROM;
        } else if (token_string.compare("WHERE") == 0) {
            return TokenType::KEYWORD_WHERE;
        } else if (std::regex_match(token_string, REGEX_INTEGER)) {
            return TokenType::INTEGER;
        } else if (std::regex_match(token_string, REGEX_LITERAL)) {
            return TokenType::LITERAL;
        } else if (std::regex_match(token_string, REGEX_IDENTIFIER)) {
            return TokenType::IDENTIFIER;
        }
        return TokenType::UNRECOGNIZED;
    }

    Token Lexer::evaluate(TokenType token_type, std::string &token_string) {
        return TokenEvaluator::for_type(token_type)(token_string);
    }
}