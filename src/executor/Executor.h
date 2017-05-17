#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "optimizer/Plan.h"

namespace db07 {
    class Executor {
    private:
        const Plan *plan;

    public:
        Executor(Plan &plan) : plan(&plan) { }

        void run();
    };
}

#endif // !EXECUTOR_H
