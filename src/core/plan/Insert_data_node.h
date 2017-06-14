#ifndef INSERT_DATA_H
#define INSERT_DATA_H

#include <memory>
#include <storage_engine/Table_definition.h>
#include "Plan_node.h"

namespace db07 {
    class Insert_data_node : public Plan_node {
    public:
        explicit Insert_data_node(std::shared_ptr<const Table_definition> &table_definition, std::vector<Row *> &rows);

        bool has_next() override;

        Row *next() override;

    private:
        const std::shared_ptr<const Table_definition> _table_definition;
        const std::vector<Row *> _rows;
        std::vector<Row *>::const_iterator _position;
    };
}


#endif
