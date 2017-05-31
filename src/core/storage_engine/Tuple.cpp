#include "Tuple.h"

using namespace db07;

Tuple::Tuple(const Tuple_description *description, Tuple_data *data) :
    m_description(description), m_data(data)
{
    m_value_indexes = new int[description->size()];
    m_data->get_indexes(*description, m_value_indexes);
}

int Tuple::compare_field(int field_index, unsigned char *to)
{
    return 0;
}
