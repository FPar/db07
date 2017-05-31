#ifndef TABLE_H
#define TABLE_H

#include <string>

#include "Column.h"
#include "Object_store_item.h"

namespace db07 {
    class Table : public Object_store_item {
    private:
        std::string m_name;
        Table_definition m_description;

    public:
        Table(std::string &name, Table_definition &description)
            : m_name(name), m_description(description)
        {
        }

        virtual std::string name() const {
            return m_name;
        }

        const Table_definition *description() const {
            return &m_description;
        }
    };
}

#endif // !TABLE_H
