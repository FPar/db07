#include "Row.h"

using namespace std;
using namespace db07;

Row::~Row()
{
	for (auto value : _values)
	{
		delete value;
	}
}

Value* Row::get(const string& field) const
{
	int index = 0;
	for (auto i = _description->cbegin(); i != _description->cend(); ++i)
	{
		if ((*i).name() == field)
		{
			return _values.at(index);
		}
	}
	throw runtime_error("Accessing non existent field from row.");
}

int Row::compare_field(const string& field, const Value& to) const
{
	Value* value = get(field);
	return value->compare(to);
}
