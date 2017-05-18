#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

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
        Type *m_type;
        bool m_not_null;

    public:
        Attribute(std::string &name, Type *type, bool not_null)
            : m_name(name), m_type(type), m_not_null(not_null)
        {
        }

        std::string name() const {
            return m_name;
        }

        Type *type() const {
            return m_type;
        };

        bool has_type_mod() const;
        int type_mod() const;

        bool not_null() const {
            return m_not_null;
        };
    };

    typedef std::vector<Attribute> Tuple_description;
}

#endif // !ATTRIBUTE_H
