#ifndef RELATION_H
#define RELATION_H

#include <string>
#include "Catalog_item.h"

namespace db07 {
    class Relation : public Catalog_item {
    private:
        std::string m_name;

    public:
        Relation(std::string &name)
            : m_name(name)
        {
        }

        virtual std::string name() const {
            return m_name;
        }
    };
}

#endif // !RELATION_H
