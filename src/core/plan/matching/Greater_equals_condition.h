#ifndef GREATER_EQUALS_CONDITION_H
#define GREATER_EQUALS_CONDITION_H

#include "Comparing_condition.h"

namespace db07
{
	class Greater_equals_condition : public Comparing_condition
	{
	public:
		Greater_equals_condition(std::string& column, Value* value)
			: Comparing_condition(column, value)
		{
		}

	protected:
		bool interpret(int compare_result) const override;
	};
}

#endif
