#ifndef COLUMN_H
#define COLUMN_H

#include <string>
#include <vector>

#include "Type.h"

namespace db07 {
    /*
     * Information about a table column.
     */
    class Column {
    private:
        std::string m_name;
        Type *m_type;
        bool m_not_null;

    public:
        Column(std::string &name, Type *type, bool not_null)
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

    typedef std::vector<Column> Table_definition;
}

#endif // !COLUMN_H
