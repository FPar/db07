#include "Equals_condition.h"

using namespace db07;

bool db07::Equals_condition::fulfil(Row& row) const
{
    return row.compare_field(_column, *_value) == 0;
}
