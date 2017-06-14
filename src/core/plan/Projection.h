#ifndef PROJECTION_H
#define PROJECTION_H

#include <memory>
#include <vector>
#include "storage_engine/Row.h"
#include "storage_engine/Table_definition.h"

namespace db07
{
	class Projection
	{
	public:
		Projection(Table_definition& input, std::vector<std::string>& columns);
		std::unique_ptr<Row> project(Row& row);

	private:
		const std::vector<std::string> _columns;
		std::shared_ptr<Table_definition> _definition;
	};
}

#endif
