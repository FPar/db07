#include "Insert_data_node.h"

bool db07::Insert_data_node::has_next() {
    return _position != _rows.end();
}

db07::Row *db07::Insert_data_node::next() {
    return *_position++;
}

db07::Insert_data_node::Insert_data_node(std::shared_ptr<const db07::Table_definition> &table_definition,
                                         std::vector<Row *> &rows) :
        _table_definition(table_definition), _rows(rows) {
    _position = _rows.begin();
}
