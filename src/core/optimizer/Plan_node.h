#ifndef PLAN_NODE_H
#define PLAN_NODE_H

#include "storage_engine/Tuple.h"

namespace db07 {
    class Plan_node {
    public:
        virtual bool has_next() = 0;
        virtual Tuple next() = 0;
    };
}

#endif // !PLAN_NODE_H
