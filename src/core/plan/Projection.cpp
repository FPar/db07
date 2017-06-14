#include "Projection.h"

using namespace std;
using namespace db07;

Projection::Projection(Table_definition& input, vector<string>& columns): _columns(columns), _definition(new Table_definition())
{
	for (auto column_name : columns)
	{
	}
}

unique_ptr<Row> Projection::project(Row& row)
{
	return unique_ptr<Row>(nullptr);
}
