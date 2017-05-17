#ifndef CATALOG_ITEM_H
#define CATALOG_ITEM_H

#include <string>

namespace db07 {
    class Catalog_item {
    public:
        virtual std::string name() const = 0;
    };
}

#endif // !CATALOG_ITEM_H
