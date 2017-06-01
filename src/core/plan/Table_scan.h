#ifndef RELATION_SCAN_H
#define RELATION_SCAN_H

#include "optimizer/Plan_node.h"
#include "plan/matching/Condition.h"
#include "storage_engine/Table.h"

namespace db07 {
    class Table_scan : public Plan_node {
    private:
        const Table* _table;
        const Condition* m_condition;

    public:
        Table_scan(Table *table, Condition *condition)
            : _table(table), m_condition(condition)
        {
        }

        bool has_next();
        Row next();
    };
}

#endif // !RELATION_SCAN_H
