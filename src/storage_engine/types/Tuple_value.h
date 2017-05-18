#ifndef TUPLE_VALUE_H
#define TUPLE_VALUE_H

#include "storage_engine/Type.h"

namespace db07 {
    class Tuple_value {
    public:
        virtual int length() const = 0;
        virtual unsigned char *data() = 0;
    };
}

#endif // !TUPLE_VALUE_H
