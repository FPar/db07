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
        Object_store(std::string name) : _name(name) {
        }

        void add(std::shared_ptr<T> &item) {
            if (contains(item->name()))
                throw object_store_item_exists(_name, item->name());

            _items.push_back(item);
        }

        std::shared_ptr<T> find(const std::string &item_name) const {
            for (auto i = _items.cbegin(); i != _items.cend(); ++i) {
                if ((**i).name() == _name) {
                    return *i;
                }
            }

            throw object_store_item_not_found(_name, item_name);
        }

    private:
        std::string _name;
        std::vector<std::shared_ptr<T>> _items;

        bool contains(const std::string &name) {
            return false;
        }
    };
}

#endif
