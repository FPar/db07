#ifndef CATALOG_H
#define CATALOG_H

#include "Object_store.h"
#include "Table.h"

namespace db07
{
	class Global_object_store
	{
	public:
		Global_object_store();

		const Object_store<Table>* relations() const
		{
			return _tables;
		}

	private:
		Object_store<Table>* _tables;
	};
}

#endif // !CATALOG_H
