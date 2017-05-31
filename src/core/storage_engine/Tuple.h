#ifndef TUPLE_H
#define TUPLE_H

#include "Tuple_data.h"

namespace db07 {
    class Tuple {
    private:
        const Tuple_description *m_description;
        Tuple_data *m_data;
        int *m_value_indexes;

    public:
        Tuple(const Tuple_description *description, Tuple_data *data);

        const Tuple_description *description() const
        {
            return m_description;
        }

        int compare_field(int field_index, unsigned char *to);
    };
}

#endif // !TUPLE_H
