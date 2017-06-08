#include "Unequals_condition.h"

using namespace db07;

bool Unequals_condition::interpret(int compare_result) const
{
	return compare_result != 0;
}
