#ifndef COLUMN_H
#define COLUMN_H

#include <vector>

#include "types/Type.h"

namespace db07 {
    /*
     * Information about a table column.
     */
    class Column {
    public:
        Column(const std::string &name, const Type &type, bool not_null)
                : _name(name), _type(&type), _not_null(not_null) {
        }

        std::string name() const {
            return _name;
        }

        const Type *type() const {
            return _type;
        }

        bool not_null() const {
            return _not_null;
        }

    private:
        std::string _name;
        const Type *_type;
        bool _not_null;
    };
}

#endif
