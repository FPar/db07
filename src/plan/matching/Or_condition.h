#ifndef OR_CONDITION_H
#define OR_CONDITION_H

#include "Condition.h"

namespace db07 {
    class Or_condition : public Condition {
    private:
        Condition *_a;
        Condition *_b;

    public:
        Or_condition(Condition *a, Condition *b)
            : _a(a), _b(b)
        {
        }

        bool fulfil(Tuple &tuple);
    };
}

#endif // !AND_CONDITION_H
