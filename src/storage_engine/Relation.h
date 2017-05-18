#ifndef RELATION_H
#define RELATION_H

#include <string>
#include "storage_engine/Catalog_item.h"
#include "storage_engine/Attribute.h"

namespace db07 {
    class Relation : public Catalog_item {
    private:
        std::string m_name;
        Tuple_description m_description;

    public:
        Relation(std::string &name, Tuple_description &description)
            : m_name(name), m_description(description)
        {
        }

        virtual std::string name() const {
            return m_name;
        }

        Tuple_description description() const {
            return m_description;
        }
    };
}

#endif // !RELATION_H
