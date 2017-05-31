#ifndef CONDITION_H
#define QUALIFICATION_H

#include "storage_engine/Tuple.h"

namespace db07 {
    class Condition {
    public:
        virtual bool fulfil(Tuple &tuple) const = 0;
    };
}

#endif // !QUALIFICATION_H
