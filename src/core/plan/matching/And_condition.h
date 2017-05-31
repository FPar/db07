#ifndef AND_CONDITION_H
#define AND_CONDITION_H

#include "Condition.h"

namespace db07 {
    class And_condition : public Condition {
    private:
        Condition *_a;
        Condition *_b;

    public:
        And_condition(Condition *a, Condition *b)
            : _a(a), _b(b)
        {
        }

        bool fulfil(Row &tuple) const;
    };
}

#endif // !AND_CONDITION_H
