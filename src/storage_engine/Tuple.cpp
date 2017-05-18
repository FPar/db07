#include "Tuple.h"

db07::Tuple::Tuple(Tuple_description *description, Tuple_data *data) :
    m_description(description), m_data(data)
{
    m_value_indexes = new int[description->size()];
    m_data->get_indexes(*description, m_value_indexes);
}