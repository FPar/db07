#include "Table.h"

using namespace db07;

void Table::insert(Row* row)
{
	_data.insert(0, row);
}
