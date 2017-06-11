#ifndef TABLE_SCAN_H
#define TABLE_SCAN_H

#include "Plan_node.h"
#include "plan/matching/Condition.h"
#include "storage_engine/Table.h"

namespace db07
{
	class Table_scan : public Plan_node
	{
	public:
		Table_scan(Table* table, Condition* condition)
			: _table(table), m_condition(condition)
		{
		}

		bool has_next() override;
		Row* next() override;

	private:
		const Table* _table;
		const Condition* m_condition;
	};
}

#endif
