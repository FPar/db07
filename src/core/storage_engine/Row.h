#ifndef TUPLE_H
#define TUPLE_H

#include "Tuple_data.h"

namespace db07 {
    class Row {
    private:
        const Table_definition *m_description;
        Tuple_data *m_data;
        int *m_value_indexes;

    public:
        Row(const Table_definition *description, Tuple_data *data);

        const Table_definition *description() const
        {
            return m_description;
        }

        int compare_field(int field_index, unsigned char *to);
    };
}

#endif // !TUPLE_H
