#ifndef ROW_H
#define ROW_H

#include <memory>
#include <vector>
#include <string>
#include "values/Value.h"

namespace db07 {
    class Row {
    public:
        Row(const std::shared_ptr<std::vector<std::unique_ptr<Value>>> &values) : _values(values) {
        }

        Value &get(unsigned int field) const;

    private:
        const std::shared_ptr<std::vector<std::unique_ptr<Value>>> _values;
    };
}

#endif
