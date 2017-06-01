#ifndef COMPARING_CONDITION_H
#define COMPARING_CONDITION_H

#include <string>
#include "Condition.h"
#include "storage_engine/values/Value.h"

namespace db07 {
    class Comparing_condition : public Condition {
    protected:
        const std::string _column;
        const Value* _value;

        virtual bool interpret(int compare_result) const = 0;

    public:
        Comparing_condition(std::string &column, Value* value) :
            _column(column), _value(value)
        {
        }

        bool fulfil(Row& row) const;
    };
}

#endif // !COMPARING_CONDITION_H
