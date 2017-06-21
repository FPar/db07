#ifndef UNEQUALS_CONDITION_H
#define UNEQUALS_CONDITION_H

#include "Comparing_condition.h"

namespace db07 {
    class Unequals_condition : public Comparing_condition {
    protected:
        bool interpret(double compare_result) const override;

    public:
        Unequals_condition(unsigned int column, std::unique_ptr<Value> value) :
                Comparing_condition(column, move(value)) {
        }
    };
}

#endif
