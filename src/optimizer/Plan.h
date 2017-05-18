#ifndef PLAN_H
#define PLAN_H

namespace db07 {
    class Plan {
    public:
        virtual void execute() = 0;
    };
}

#endif // !PLAN_H