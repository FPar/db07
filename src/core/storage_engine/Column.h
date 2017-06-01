#ifndef COLUMN_H
#define COLUMN_H

#include <string>
#include <vector>

#include "types/Type.h"

namespace db07 {
    /*
     * Information about a table column.
     */
    class Column {
    private:
        std::string _name;
        Type *m_type;
        bool m_not_null;

    public:
        Column(std::string &name, Type *type, bool not_null)
            : _name(name), m_type(type), m_not_null(not_null)
        {
        }

        std::string name() const {
            return _name;
        }

        Type *type() const {
            return m_type;
        };

        bool not_null() const {
            return m_not_null;
        };
    };

    typedef std::vector<Column> Table_definition;
}

#endif // !COLUMN_H
