#ifndef AND_CONDITION_H
#define AND_CONDITION_H

#include <memory>
#include "Condition.h"

namespace db07 {
    class And_condition : public Condition {
    private:
        std::unique_ptr<Condition> _a;
        std::unique_ptr<Condition> _b;

    public:
        And_condition(std::unique_ptr<Condition> a, std::unique_ptr<Condition> b) :
            _a(move(a)), _b(move(b))
        {
        }

        bool fulfil(const Row & tuple) const;
    };
}

#endif // !AND_CONDITION_H
