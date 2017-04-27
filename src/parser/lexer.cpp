#include "lexer.h"

namespace db07 {
    void Lexer::tokenize(std::string &input) {
        std::string lexeme;
        std::string::iterator input_iterator = input.begin();
        while (input_iterator < input.end()) {
            char chr = *input_iterator;
            if (is_delimiter(chr)) {
                TokenType token_type = recognize_lexeme(lexeme);
                if (token_type == TokenType::UNRECOGNIZED) {
                    std::cerr << "Unrecognized lexeme " << lexeme << "\n";
                    return;
                }
                std::cout << token_type << " ";
                lexeme = {};
            } else {
                lexeme += chr;
            }
            input_iterator++;
        }
        TokenType token_type = recognize_lexeme(lexeme);
        if (token_type == TokenType::UNRECOGNIZED) {
            std::cerr << "Unrecognized lexeme " << lexeme << "\n";
            return;
        }
        std::cout << token_type << " ";
    }

    bool Lexer::is_delimiter(char chr) {
        return chr == ' ';
    }

    Lexer::TokenType Lexer::recognize_lexeme(std::string &lexeme) {
        static const std::regex REGEX_INTEGER("[0-9]+", std::regex_constants::icase);
        static const std::regex REGEX_LITERAL("\'.*\'", std::regex_constants::icase);
        static const std::regex REGEX_IDENTIFIER("[a-z][a-z0-9_]*", std::regex_constants::icase);

        if (lexeme.compare("==") == 0) {
            return TokenType::OPERATOR_EQ;
        } else if (lexeme.compare("!=") == 0) {
            return TokenType::OPERATOR_NEQ;
        } else if (lexeme.compare("SELECT") == 0) {
            return TokenType::KEYWORD_SELECT;
        } else if (lexeme.compare("FROM") == 0) {
            return TokenType::KEYWORD_FROM;
        } else if (lexeme.compare("WHERE") == 0) {
            return TokenType::KEYWORD_WHERE;
        } else if (std::regex_match(lexeme, REGEX_INTEGER)) {
            return TokenType::INTEGER;
        } else if (std::regex_match(lexeme, REGEX_LITERAL)) {
            return TokenType::LITERAL;
        } else if (std::regex_match(lexeme, REGEX_IDENTIFIER)) {
            return TokenType::IDENTIFIER;
        }
        return TokenType::UNRECOGNIZED;
    }
}