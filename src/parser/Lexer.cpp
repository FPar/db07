#include "parser/Lexer.h"
#include "parser/Token_recognizer.h"

namespace db07 {
    std::list<Token> Lexer::tokenize(std::string &input) {
        std::list<Token> tokens;
        std::string token_string;
        for (std::string::iterator input_iterator = input.begin();
             input_iterator != input.end();
             input_iterator++) {
            char chr = *input_iterator;
            if (is_delimiter(chr)) {
                token_type token_type = Token_recognizer::recognize(token_string);
                Token token = Token_evaluator::for_type(token_type)(token_string);
                tokens.push_back(token);
                if (token_type == token_type::UNRECOGNIZED) {
                    return tokens;
                }
                token_string = {};
            } else {
                token_string += chr;
            }
        }
        token_type token_type = Token_recognizer::recognize(token_string);
        Token token = Token_evaluator::for_type(token_type)(token_string);
        tokens.push_back(token);
        return tokens;
    }

    bool Lexer::is_delimiter(char chr) {
        return chr == ' ';
    }
}