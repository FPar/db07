#ifndef ATTRIBUTE_H
#define ATTRIBUTE

#include <string>
#include <vector>

#include "storage_engine/Type.h"

namespace db07 {
    /*
     * Information about a table column.
     */
    class Attribute {
    private:
        std::string m_name;

    public:
        std::string name() const {
            return m_name;
        }

        Type type() const;
        bool has_type_mod() const;
        int type_mod() const;
        bool not_null() const;
    };

    typedef std::vector<Attribute> Tuple_description;
}

#endif // !ATTRIBUTE_H
