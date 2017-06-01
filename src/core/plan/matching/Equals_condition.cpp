#include "Equals_condition.h"

using namespace db07;

bool Equals_condition::interpret(int compare_result) const
{
    return compare_result == 0;
}
