#ifndef DB07_TOKEN_RECOGNIZER_H
#define DB07_TOKEN_RECOGNIZER_H

#include <string>
#include <functional>
#include<list>
#include<regex>
#include "token_type.h"

namespace db07 {
    class TokenRecognizer {
    private:
        class Rule {
        private:
            const std::function<bool(std::string &)> predicate_;
            const TokenType token_type_;
        public:
            Rule(const std::function<bool(std::string &)> &predicate_, const TokenType token_type_);

            bool matches(std::string &token_string) const;

            TokenType token_type() const;
        };

        static const std::list<Rule> RULES;
        static const std::regex REGEX_INTEGER;
        static const std::regex REGEX_LITERAL;
        static const std::regex REGEX_IDENTIFIER;

    public:
        static TokenType recognize(std::string &token_string);
    };
}

#endif
