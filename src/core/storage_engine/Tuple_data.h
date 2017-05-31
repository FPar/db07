#ifndef TUPLE_DATA_H
#define TUPLE_DATA_H

#include <vector>

#include "Column.h"
#include "types/Tuple_value.h"

namespace db07 {
    class Tuple_data {
    private:
        unsigned char *m_data;

    public:
        Tuple_data(std::vector<Tuple_value> &values);
        ~Tuple_data();

        void get_indexes(const Table_definition &description, int *indexes);
        void set_value(int position, Tuple_value &value);
    };
}

#endif // !TUPLE_DATA_H
