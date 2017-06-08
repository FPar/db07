#ifndef INSERT_PLAN_H
#define INSERT_PLAN_H

#include "Plan.h"

namespace db07
{
	class Insert_plan : public Plan
	{
	public:
		void execute() override;
	};
}

#endif // !INSERT_PLAN_H