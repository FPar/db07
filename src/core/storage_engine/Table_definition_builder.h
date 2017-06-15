#ifndef TABLE_DEFINITION_BUILDER_H
#define TABLE_DEFINITION_BUILDER_H

#include "types/Type.h"
#include "Table_definition.h"

namespace db07 {
    class Table_definition_builder {
    public:
        void add_column(const std::string &name, const Type &type);

        Table_definition get() const;

    private:
        std::vector<Column> _columns;
    };
}

#endif
