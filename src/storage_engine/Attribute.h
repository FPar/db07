#ifndef ATTRIBUTE_H
#define ATTRIBUTE

#include <string>
#include "storage_engine/Type.h"

namespace db07 {
    /*
     * Information about a table column.
     */
    struct Attribute {
        std::string name() const;
        Type type() const;
        bool has_type_mod() const;
        int type_mod() const;
        bool not_null() const;
    };
}

#endif // !ATTRIBUTE_H
