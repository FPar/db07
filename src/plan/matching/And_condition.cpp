#include "And_condition.h"

using namespace db07;

bool And_condition::fulfil(Tuple &tuple)
{
    return _a->fulfil(tuple) && _b->fulfil(tuple);
}
