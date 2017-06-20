#ifndef TABLE_SCAN_H
#define TABLE_SCAN_H

#include "Plan_node.h"
#include <plan/matching/Condition.h>
#include <storage_engine/Table.h>

namespace db07 {
    class Table_scan : public Plan_node {
    public:
        Table_scan(const std::shared_ptr<Table> &table, std::unique_ptr<Condition> condition)
                : _table(table), _condition(move(condition)), it(table->data().begin()) {
        }

        bool has_next() override;

        std::shared_ptr<Row> next() override;

    private:
        const std::shared_ptr<Table> _table;
        const std::unique_ptr<Condition> _condition;
        Btree::iterator it;
    };
}

#endif
