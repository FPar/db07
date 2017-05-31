#include "Relation_scan.h"

using namespace db07;

bool Relation_scan::has_next()
{
    return false;
}

Tuple Relation_scan::next()
{
    const Tuple_description *desc = m_relation->description();
    std::vector<Tuple_value> values;
    Tuple_data *data = new Tuple_data(values);
    return Tuple(desc, data);
}
