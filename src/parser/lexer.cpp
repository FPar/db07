#include "lexer.h"
#include "token_recognizer.h"

namespace db07 {
    std::list<Token> Lexer::tokenize(std::string &input) {
        std::list<Token> tokens;
        std::string token_string;
        for (std::string::iterator input_iterator = input.begin();
             input_iterator != input.end();
             input_iterator++) {
            char chr = *input_iterator;
            if (is_delimiter(chr)) {
                TokenType token_type = TokenRecognizer::recognize(token_string);
                Token token = TokenEvaluator::for_type(token_type)(token_string);
                tokens.push_back(token);
                if (token_type == TokenType::UNRECOGNIZED) {
                    return tokens;
                }
                token_string = {};
            } else {
                token_string += chr;
            }
        }
        TokenType token_type = TokenRecognizer::recognize(token_string);
        Token token = TokenEvaluator::for_type(token_type)(token_string);
        tokens.push_back(token);
        return tokens;
    }

    bool Lexer::is_delimiter(char chr) {
        return chr == ' ';
    }
}