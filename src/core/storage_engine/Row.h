#ifndef ROW_H
#define ROW_H

#include <vector>
#include <string>
#include "Column.h"
#include "values/Value.h"

namespace db07
{
	class Row
	{
	public:
		Row(const Table_definition* description, std::vector<Value*>& values) :
			_description(description), _values(values)
		{
		}

		~Row();

		const Table_definition* description() const
		{
			return _description;
		}

		Value* get(const std::string& field) const;
		int compare_field(const std::string& field, const Value& to) const;

	private:
		const Table_definition* _description;
		const std::vector<Value*> _values;
	};
}

#endif
