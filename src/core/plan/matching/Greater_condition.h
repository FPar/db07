#ifndef GREATER_CONDITION_H
#define GREATER_CONDITION_H

#include "Comparing_condition.h"

namespace db07
{
	class Greater_condition : public Comparing_condition
	{
	protected:
		bool interpret(int compare_result) const override;

	public:
		Greater_condition(unsigned int column, Value* value) :
			Comparing_condition(column, value)
		{
		}
	};
}

#endif
