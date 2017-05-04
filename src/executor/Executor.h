#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "optimizer/Query_plan.h"

namespace db07 {
    class Executor {
    private:
        const Query_plan *plan;

    public:
        Executor(Query_plan &plan) : plan(&plan) { }

        void run();
    };
}

#endif // !EXECUTOR_H
