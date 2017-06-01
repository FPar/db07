#include "Relation_scan.h"

using namespace db07;

bool Relation_scan::has_next()
{
    return false;
}

Row Relation_scan::next()
{
    /*const Table_definition *desc = m_relation->description();
    std::vector<Tuple_value> values;
    Tuple_data *data = new Tuple_data(values);
    return Row(desc, data);*/
    return Row(nullptr, std::vector<Value*>());
}
