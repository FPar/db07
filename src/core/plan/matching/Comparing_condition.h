#ifndef COMPARING_CONDITION_H
#define COMPARING_CONDITION_H

#include "Condition.h"
#include "storage_engine/values/Value.h"

namespace db07 {
    class Comparing_condition : public Condition {
    public:
        Comparing_condition(unsigned int column, std::unique_ptr<Value> value) :
                _column(column), _value(move(value)) {
        }

        bool fulfil(Row &row) const override;

    protected:
        const unsigned int _column;
        const std::unique_ptr<Value> _value;

        virtual bool interpret(int compare_result) const = 0;
    };
}

#endif
