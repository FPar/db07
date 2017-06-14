#include "Comparing_condition.h"

using namespace db07;

bool Comparing_condition::fulfil(Row& row) const
{
    return interpret(row.get(_column)->compare(*_value));
}
