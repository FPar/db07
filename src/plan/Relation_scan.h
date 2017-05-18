#ifndef RELATION_SCAN_H
#define RELATION_SCAN_H

#include "optimizer/Plan_node.h"
#include "plan/matching/Condition.h"
#include "storage_engine/Relation.h"

namespace db07 {
    class Relation_scan : public Plan_node {
    private:
        const Relation *m_relation;
        const Condition *m_condition;

    public:
        Relation_scan(Relation *relation, Condition *condition)
            : m_relation(relation), m_condition(condition)
        {
        }

        bool has_next();
        Tuple next();
    };
}

#endif // !RELATION_SCAN_H
