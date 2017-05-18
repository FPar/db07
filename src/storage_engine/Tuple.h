#ifndef TUPLE_H
#define TUPLE_H

#include "storage_engine/Tuple_data.h"

namespace db07 {
    class Tuple {
    private:
        const Tuple_description *m_description;
        Tuple_data *m_data;
        int *m_value_indexes;

    public:
        Tuple(Tuple_description *description, Tuple_data *data);

        const Tuple_description *description() const
        {
            return m_description;
        }
    };
}

#endif // !TUPLE_H
