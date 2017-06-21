#include "Greater_equals_condition.h"

bool db07::Greater_equals_condition::interpret(double compare_result) const
{
	return compare_result >= 0;
}
