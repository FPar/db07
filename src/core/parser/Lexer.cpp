#include "parser/Lexer.h"
#include "parser/Token_recognizer.h"

namespace db07 {
    std::vector<Token> Lexer::tokenize(std::string &input) {
        std::vector<Token> tokens;

        std::string token_string;
        token_type token_type = token_type::UNRECOGNIZED;
        for (auto token_chr = input.begin(), previous_token_chr = token_chr; token_chr != input.end(); token_chr++) {
            token_string += *token_chr;

            if (!Token_recognizer::can_recognize(token_string)) {
                token_string.pop_back();
                Token token = Token_evaluator::for_type(token_type)(token_string);
                tokens.push_back(token);
                if (token_type == token_type::UNRECOGNIZED) {
                    return tokens; // TODO throw exception instead
                }

                // recognized, no more prefixes
                token_string.clear();
                token_type = token_type::UNRECOGNIZED;
                token_chr = previous_token_chr;
            }

            if (!token_string.empty()) {
                // only if not recognized fully in if-statement above
                token_type = Token_recognizer::recognize(token_string);
                if (token_type != token_type::UNRECOGNIZED) {
                    // recognized with prefix
                    previous_token_chr = token_chr;
                }
            }
        }

        Token token = Token_evaluator::for_type(token_type)(token_string);
        tokens.push_back(token);
        return tokens;
    }
}