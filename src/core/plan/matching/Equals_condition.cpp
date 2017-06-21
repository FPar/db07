#include "Equals_condition.h"

using namespace db07;

bool Equals_condition::interpret(double compare_result) const
{
	return compare_result == 0;
}
