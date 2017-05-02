#include "lexer.h"

namespace db07 {
    void Lexer::tokenize(std::string &input, std::list<TokenType> &token_types) {
        std::string token_string;
        std::string::iterator input_iterator = input.begin();
        while (input_iterator < input.end()) {
            char chr = *input_iterator;
            if (is_delimiter(chr)) {
                TokenType token_type = recognize_token_type(token_string);
                token_types.push_back(token_type);
                if (token_type == TokenType::UNRECOGNIZED) {
                    return;
                }
                token_string = {};
            } else {
                token_string += chr;
            }
            input_iterator++;
        }
        TokenType token_type = recognize_token_type(token_string);
        token_types.push_back(token_type);
        if (token_type == TokenType::UNRECOGNIZED) {
            return;
        }
    }

    bool Lexer::is_delimiter(char chr) {
        return chr == ' ';
    }

    TokenType Lexer::recognize_token_type(std::string &token_string) {
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
}