#ifndef UNEQUALS_CONDITION_H
#define UNEQUALS_CONDITION_H

#include "Comparing_condition.h"

namespace db07
{
	class Unequals_condition : public Comparing_condition
	{
	protected:
		bool interpret(int compare_result) const override;

	public:
		Unequals_condition(std::string& column, Value* value) :
			Comparing_condition(column, value)
		{
		}
	};
}

#endif
