#ifndef OBJECT_STORE_H
#define OBJECT_STORE_H

#include <vector>
#include "Table.h"
#include "object_store_item_exists.h"
#include "object_store_item_not_found.h"

namespace db07 {
    template<typename T>
    class Object_store {
    public:
        Object_store(std::string &name) : _name(name) {
        }

        void add(T *item) {
            if (try_find(item->name()))
                throw object_store_item_exists(_name, item->name());

            _items.push_back(item);
        }

        T *find(std::string &item_name) const {
            T *item = try_find(item_name);
            if (!item)
                throw object_store_item_not_found(_name, item_name);

            return item;
        }

    private:
        std::string _name;
        std::vector<T *> _items;

        T *try_find(std::string &name) const {
            for (auto i = _items.cbegin(); i != _items.cend(); ++i) {
                if ((**i).name() == name) {
                    return *i;
                }
            }
            return nullptr;
        }
    };
}

#endif
