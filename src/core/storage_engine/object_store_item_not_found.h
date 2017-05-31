#ifndef CATALOG_ITEM_NOT_FOUND_H
#define CATALOG_ITEM_NOT_FOUND_H

#include <stdexcept>
#include <string>

namespace db07 {
    class object_store_item_not_found : public std::runtime_error {
    private:
        const std::string m_catalog_name;
        const std::string m_item_name;

    public:
        object_store_item_not_found(std::string &catalog_name, std::string &item_name) :
            runtime_error("Cannot find item with that name in the catalog."),
            m_catalog_name(catalog_name),
            m_item_name(m_item_name)
        {
        }

        const std::string &catalog_name() const {
            return m_catalog_name;
        }

        const std::string item_name() const {
            return m_item_name;
        }
    };
}

#endif // !CATALOG_ITEM_EXISTS_H
