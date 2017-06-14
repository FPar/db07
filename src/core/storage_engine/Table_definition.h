#ifndef TABLE_DEFINITION_H
#define TABLE_DEFINITION_H

#include <vector>
#include "Column.h"

namespace db07
{
	class Table_definition
	{
	public:
		Table_definition()
		{
		}

		int column_id(std::string& name) const;

		void add_column(Column& column);

		const std::vector<Column>& columns() const
		{
			return _columns;
		}

	private:
		std::vector<Column> _columns;
	};
}

#endif
