#ifndef CONDITION_H
#define CONDITION_H

#include "storage_engine/Row.h"

namespace db07 {
    class Condition {
    public:
	    virtual ~Condition() = default;
	    virtual bool fulfil(Row &tuple) const = 0;
    };
}

#endif // !CONDITION_H
