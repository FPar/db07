#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>

#include "Column.h"
#include "values/Value.h"

namespace db07 {
    class Row {
    private:
        const Table_definition* _description;
        const std::vector<Value*> _values;

    public:
        Row(const Table_definition *description, std::vector<Value*> &values) :
            _description(description), _values(values) {};

        const Table_definition *description() const
        {
            return _description;
        }

        Value* const get(const std::string &field) const;
        int compare_field(const std::string &field, const Value &to) const;
    };
}

#endif // !TUPLE_H
