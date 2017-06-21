#include "Less_condition.h"

using namespace db07;

bool Less_condition::interpret(double compare_result) const
{
    return compare_result < 0;
}
