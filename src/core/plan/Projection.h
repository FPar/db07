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
		std::shared_ptr<Row> project(Row& row);

        std::shared_ptr<Table_definition> definition() {
            return _definition;
        }

	private:
		std::vector<int> _columns;
		std::shared_ptr<Table_definition> _definition;
	};
}

#endif
