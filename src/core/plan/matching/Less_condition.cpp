#include "Less_condition.h"

using namespace db07;

bool Less_condition::interpret(int compare_result) const
{
    return compare_result < 0;
}
