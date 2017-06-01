#ifndef EQUALS_CONDITION_H
#define EQUALS_CONDITION_H

#include <string>
#include "Comparing_condition.h"

namespace db07 {
    class Equals_condition : public Comparing_condition {
    protected:
        bool interpret(int compare_result) const;

    public:
        Equals_condition(std::string &column, Value* value) :
            Comparing_condition(column, value)
        {
        }
    };
}

#endif // !EQUALS_CONDITION_H
