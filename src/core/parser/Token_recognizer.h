#ifndef TOKEN_RECOGNIZER_H
#define TOKEN_RECOGNIZER_H

#include <string>
#include <functional>
#include <list>
#include <regex>
#include "parser/token_type.h"

namespace db07 {
    class Token_recognizer {
    private:
        class Rule {
        private:
            const std::function<bool(std::string &)> _predicate;
            const token_type _token_type;
        public:
            Rule(const std::function<bool(std::string &)> &predicate_, const token_type token_type_)
                : _predicate(predicate_), _token_type(token_type_)
            {
            }

            bool matches(std::string &token_string) const;

            token_type type() const;
        };

        static const std::list<Rule> RULES;

    public:
        static token_type recognize(std::string &token_string);
    };
}

#endif
