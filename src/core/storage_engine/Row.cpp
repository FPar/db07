#include "Row.h"

using namespace db07;

Row::Row(const Table_definition *description, Tuple_data *data) :
    m_description(description), m_data(data)
{
    m_value_indexes = new int[description->size()];
    m_data->get_indexes(*description, m_value_indexes);
}

int Row::compare_field(int field_index, unsigned char *to)
{
    return 0;
}
