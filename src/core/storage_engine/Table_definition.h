#ifndef TABLE_DEFINITION_H
#define TABLE_DEFINITION_H

#include <vector>
#include <memory>
#include "Column.h"

namespace db07 {
    class Table_definition {
    public:
        Table_definition(std::vector<Column> columns) : _columns(columns) {
        }

        int column_id(std::string &name) const;

        const std::vector<Column> &columns() const {
            return _columns;
        }

    private:
        std::vector<Column> _columns;
    };
}

#endif
