#ifndef LESS_EQUALS_CONDITION_H
#define LESS_EQUALS_CONDITION_H

#include "Comparing_condition.h"

namespace db07 {
    class Less_equals_condition : public Comparing_condition {
    public:
        Less_equals_condition(unsigned int column, Value *value)
                : Comparing_condition(column, value) {
        }

    protected:
        bool interpret(int compare_result) const override;
    };
}

#endif
