#ifndef CATALOG_H
#define CATALOG_H

#include <memory>
#include "Object_store.h"
#include "Table.h"

namespace db07 {
    class Global_object_store {
    public:
        Global_object_store() : _tables("tables") {}

        Object_store<Table> &tables() {
            return _tables;
        }

    private:
        Object_store<Table> _tables;
    };
}

#endif // !CATALOG_H
