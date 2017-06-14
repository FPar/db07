#ifndef CATALOG_COLLECTION_H
#define CATALOG_COLLECTION_H

#include <vector>
#include "Table.h"
#include "object_store_item_exists.h"
#include "object_store_item_not_found.h"

namespace db07
{
	template <typename T>
	class Object_store : public Table
	{
	public:
		Object_store(std::string& name, Table_definition& definition) : Table(name, definition)
		{
		}

		void add(T* item)
		{
			if (try_find(item->name()))
				throw object_store_item_exists(name(), item->name());

			m_items.push_back(item);
		}

		T* find(std::string& item_name) const
		{
			T* item = try_find(item_name);
			if (!item)
				throw object_store_item_not_found(name(), item_name);

			return item;
		}

	private:
		std::vector<T *> m_items;

		T* try_find(std::string& name) const
		{
			for (auto i = m_items.cbegin(); i != m_items.cend(); ++i)
			{
				if ((**i).name() == name)
				{
					return *i;
				}
			}
			return nullptr;
		}
	};
}

#endif // !CATALOG_COLLECTION_H
