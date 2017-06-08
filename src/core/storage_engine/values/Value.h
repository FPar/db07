#ifndef VALUE_H
#define VALUE_H

#include "storage_engine/types/Type.h"

namespace db07
{
	class Value
	{
	public:
		virtual ~Value()
		{
		}

		virtual Type* type() = 0;
		virtual int compare(const Value& to) = 0;
	};
}

#endif // !VALUE_H
