#ifndef CATALOG_ITEM_NOT_FOUND_H
#define CATALOG_ITEM_NOT_FOUND_H

#include <stdexcept>
#include <string>

namespace db07 {
    class object_store_item_not_found : public std::runtime_error {
    private:
        const std::string _catalog_name;
        const std::string _item_name;

    public:
        object_store_item_not_found(const std::string &catalog_name, const std::string &item_name) :
            runtime_error("Cannot find item with that name in the catalog."),
            _catalog_name(catalog_name),
            _item_name(item_name)
        {
        }

        const std::string &catalog_name() const {
            return _catalog_name;
        }

        const std::string item_name() const {
            return _item_name;
        }
    };
}

#endif // !CATALOG_ITEM_EXISTS_H
