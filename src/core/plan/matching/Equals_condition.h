#ifndef EQUALS_CONDITION_H
#define EQUALS_CONDITION_H

#include "Comparing_condition.h"

namespace db07 {
    class Equals_condition : public Comparing_condition {
    protected:
        bool interpret(int compare_result) const override;

    public:
        Equals_condition(unsigned int column, Value *value) :
                Comparing_condition(column, value) {
        }
    };
}

#endif // !EQUALS_CONDITION_H
