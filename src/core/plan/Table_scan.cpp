#include "Table_scan.h"

using namespace db07;

bool Table_scan::has_next()
{
    return false;
}

Row* Table_scan::next()
{
    std::vector<Value*> values;
    return new Row(values);
}
