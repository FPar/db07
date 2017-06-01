#ifndef GREATER_CONDITION_H
#define GREATER_CONDITION_H

#include "Comparing_condition.h"

namespace db07 {
    class Greater_condition : public Comparing_condition {
    protected:
        bool interpret(int compare_result) const;

    public:
        Greater_condition(std::string& column, Value* value) :
            Comparing_condition(column, value)
        {
        }
    };
}

#endif // !GREATER_CONDITION_H