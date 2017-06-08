#include "Greater_condition.h"

using namespace db07;

bool Greater_condition::interpret(int compare_result) const
{
	return compare_result > 0;
}
