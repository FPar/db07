#include "Insert_plan.h"

using namespace db07;

void Insert_plan::execute()
{
	while (_source->has_next())
	{
		Row* current = _source->next();
		_target->insert(current);
		++_rows_inserted;
	}
}
