#ifndef TABLE_H
#define TABLE_H

#include <string>

#include "Column.h"
#include "Object_store_item.h"

namespace db07
{
	class Table : public Object_store_item
	{
	public:
		Table(std::string& name, Table_definition& definition)
			: _name(name), _definition(definition)
		{
		}

		virtual ~Table()
		{
		}

		std::string name() const override
		{
			return _name;
		}

		const Table_definition* description() const
		{
			return &_definition;
		}

	private:
		std::string _name;
		Table_definition _definition;
	};
}

#endif // !TABLE_H
