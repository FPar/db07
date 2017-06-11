#ifndef INSERT_PLAN_H
#define INSERT_PLAN_H

#include "Plan.h"
#include "plan/Plan_node.h"
#include "storage_engine/Table.h"

namespace db07
{
	class Insert_plan : public Plan
	{
	public:
		Insert_plan(Plan_node* source, Table* target) : _source(source), _target(target)
		{
		}

		void execute() override;

		int rows_inserted() const
		{
			return _rows_inserted;
		}

	private:
		Plan_node* _source;
		Table* _target;
		int _rows_inserted = 0;
	};
}

#endif
