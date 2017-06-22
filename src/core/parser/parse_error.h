#ifndef DB07_PARSE_ERROR_H
#define DB07_PARSE_ERROR_H

#include <stdexcept>
#include <vector>
#include "token_type.h"

namespace db07 {
    class parse_error : public std::runtime_error {
    private:
        std::vector<token_type> _expected;
        token_type _actual;

    public:
        parse_error(std::vector<token_type> expected, token_type actual)
                : runtime_error("Parse error"),
                  _expected(expected),
                  _actual(actual) {
        }

        const std::vector<token_type> &expected() const {
            return _expected;
        }

        const token_type &actual() const {
            return _actual;
        }
    };
}

#endif //DB07_PARSE_ERROR_H
