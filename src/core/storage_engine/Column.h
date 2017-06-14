#ifndef COLUMN_H
#define COLUMN_H

#include <vector>

#include "types/Type.h"

namespace db07
{
	/*
	 * Information about a table column.
	 */
	class Column
	{
	public:
		Column(std::string& name, Type* type, bool not_null)
			: _name(name), _type(type), _not_null(not_null)
		{
		}

		std::string name() const
		{
			return _name;
		}

		Type* type() const
		{
			return _type;
		}

		bool not_null() const
		{
			return _not_null;
		}

	private:
		std::string _name;
		Type* _type;
		bool _not_null;
	};
}

#endif // !COLUMN_H
