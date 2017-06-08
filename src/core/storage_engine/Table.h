#ifndef TABLE_H
#define TABLE_H

#include "Column.h"
#include "Object_store_item.h"
#include "Row.h"
#include "Btree.h"

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

		void insert(Row* row);

	private:
		std::string _name;
		Table_definition _definition;
		Btree _data;
	};
}

#endif
