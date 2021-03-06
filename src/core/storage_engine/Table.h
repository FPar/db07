#ifndef TABLE_H
#define TABLE_H

#include <memory>
#include "Table_definition.h"
#include "Column.h"
#include "Object_store_item.h"
#include "Row.h"
#include "Btree.h"

namespace db07 {
    class Table : public Object_store_item {
    public:
        Table(std::string &name, std::shared_ptr<Table_definition> &definition)
                : _name(name), _definition(definition) {
        }

        virtual ~Table() {
        }

        std::string name() const override {
            return _name;
        }

        std::shared_ptr<Table_definition> definition() {
            return _definition;
        }

        Btree &data() {
            return _data;
        }

        void insert(std::shared_ptr<Row> &row);

    private:
        std::string _name;
        std::shared_ptr<Table_definition> _definition;
        Btree _data;
    };
}

#endif
