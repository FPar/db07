#ifndef VALUE_H
#define VALUE_H

#include "storage_engine/types/Type.h"

namespace db07 {
    class Value {
    private:

    public:
        virtual ~Value() {};
        
        virtual Type* type() = 0;
        virtual int compare(Value& to) = 0;
    };
}

#endif // !VALUE_H
