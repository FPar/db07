#ifndef CATALOG_H
#define CATALOG_H

#include "storage_engine/Catalog.h"
#include "storage_engine/Relation.h"

namespace db07 {
    class Global_catalog {
    private:
        Catalog<Relation> m_relations;

    public:
        Catalog<Relation> relations() {
            return m_relations;
        }
    };
}

#endif // !CATALOG_H
