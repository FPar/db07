#ifndef INSERT_DATA_H
#define INSERT_DATA_H

#include <memory>
#include <storage_engine/Table_definition.h>
#include "Plan_node.h"

namespace db07 {
    class Insert_data_node : public Plan_node {
    public:
        explicit Insert_data_node(const std::shared_ptr<Table_definition> &table_definition,
                                  std::unique_ptr<std::vector<std::shared_ptr<Row>>> rows);

        bool fetch_next() override;

        std::shared_ptr<Row> next() override;

        std::shared_ptr<Table_definition> definition() const override;

    private:
        const std::shared_ptr<Table_definition> _table_definition;
        const std::unique_ptr<std::vector<std::shared_ptr<Row>>> _rows;
        std::vector<std::shared_ptr<Row>>::iterator _position;
    };
}


#endif
