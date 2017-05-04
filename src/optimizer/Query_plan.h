#ifndef QUERY_PLAN_H
#define QUERY_PLAN_H

#include "nodes/cmdType.h"

namespace db07 {
    struct Query_plan {
        const cmdType operation;
    };
}

#endif // !QUERY_PLAN_H
