#ifndef CATALOG_H
#define CATALOG_H

#include "Object_store.h"
#include "Table.h"

namespace db07 {
    class Global_object_store {
    private:
        Object_store<Table> m_relations;

    public:
        Object_store<Table> relations() {
            return m_relations;
        }
    };
}

#endif // !CATALOG_H
