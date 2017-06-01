#ifndef TABLE_H
#define TABLE_H

#include <string>

#include "Column.h"
#include "Object_store_item.h"

namespace db07 {
    class Table : public Object_store_item {
    private:
        std::string _name;
        Table_definition _description;

    public:
        Table(std::string &name, Table_definition &description)
            : _name(name), _description(description)
        {
        }

        virtual std::string name() const {
            return _name;
        }

        const Table_definition *description() const {
            return &_description;
        }
    };
}

#endif // !TABLE_H
