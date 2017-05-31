#ifndef CATALOG_COLLECTION_H
#define CATALOG_COLLECTION_H

#include <string>
#include <vector>
#include "storage_engine/catalog_item_exists.h"
#include "storage_engine/catalog_item_not_found.h"
#include "storage_engine/Relation.h"

namespace db07 {
    template <typename T> class Catalog : public Relation {
    private:
        std::vector<T *> m_items;

        T *try_find(std::string &name) const {
            for (auto i = m_items.cbegin(); i != m_items.cend; ++i) {
                if ((**i).name() == name) {
                    return *i;
                }
            }
            return nullptr;
        }

    public:
        Catalog(std::string name) : T(name)
        {
        }

        void add(T *item) {
            if (try_find(item->name()))
                throw catalog_item_exists(name(), item->name());

            m_items.push_back(item);
        }

        T *find(std::string &item_name) const {
            T *item = try_find(item_name);
            if (!item)
                throw catalog_item_not_found(name(), item_name);

            return item;
        }
    };
}

#endif // !CATALOG_COLLECTION_H
