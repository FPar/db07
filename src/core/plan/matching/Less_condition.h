#ifndef LESS_CONDITION_H
#define LESS_CONDITION_H

#include "Comparing_condition.h"

namespace db07
{
	class Less_condition : public Comparing_condition
	{
	protected:
		bool interpret(int compare_result) const override;

	public:
		Less_condition(std::string& column, Value* value) :
			Comparing_condition(column, value)
		{
		}
	};
}

#endif
