#include "Relation_scan.h"

using namespace db07;

bool Relation_scan::has_next()
{
    return false;
}

Tuple Relation_scan::next()
{
    Tuple_description desc = m_relation->description();
    return Tuple(&desc, new Tuple_data(std::vector<Tuple_value>()));
}
