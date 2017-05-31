#ifndef CATALOG_ITEM_EXISTS_H
#define CATALOG_ITEM_EXISTS_H

#include <stdexcept>
#include <string>

namespace db07 {
    class catalog_item_exists : public std::runtime_error {
    private:
        const std::string m_catalog_name;
        const std::string m_item_name;

    public:
        catalog_item_exists(std::string &catalog_name, std::string &item_name) :
            runtime_error("Cannot create two items in a catalog with the same name."),
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
