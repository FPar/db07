#ifndef CATALOG_ITEM_H
#define CATALOG_ITEM_H

#include <string>

namespace db07 {
    class Object_store_item {
    public:
		virtual ~Object_store_item()
		{
		}

        virtual std::string name() const = 0;
    };
}

#endif // !CATALOG_ITEM_H
