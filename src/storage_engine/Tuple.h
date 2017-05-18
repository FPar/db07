#ifndef TUPLE_H
#define TUPLE_H

#include "storage_engine/Tuple_data.h"
#include "storage_engine/Tuple_description.h"

namespace db07 {
    class Tuple {
    private:
        Tuple_description *description;
        Tuple_data *data;
    };
}

#endif // !TUPLE_H
