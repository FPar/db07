#ifndef EQUALS_CONDITION_H
#define EQUALS_CONDITION_H

#include <string>
#include "Condition.h"
#include "storage_engine/values/Value.h"

namespace db07 {
    class Equals_condition : public Condition {
    private:
        const std::string _column;
        const Value* _value;

    public:
        Equals_condition(std::string column, Value* value) :
            _column(column), _value(value)
        {
        }

        bool fulfil(Row& row) const;
    };
}

#endif // !EQUALS_CONDITION_H
