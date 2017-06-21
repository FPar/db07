#include "Greater_condition.h"

using namespace db07;

bool Greater_condition::interpret(double compare_result) const
{
	return compare_result > 0;
}
