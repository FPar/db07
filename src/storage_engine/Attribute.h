#ifndef ATTRIBUTE_H
#define ATTRIBUTE

#include <string>
#include <vector>

#include "storage_engine/Type.h"

namespace db07 {
    /*
     * Information about a table column.
     */
    struct Attribute {
        std::string name() const {
            return attr_name;
        }

        Type type() const;
        bool has_type_mod() const;
        int type_mod() const;
        bool not_null() const;

    private:
        std::string attr_name;
    };

    typedef std::vector<Attribute> Tuple_description;
}

#endif // !ATTRIBUTE_H
