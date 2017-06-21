#include "Insert_data_node.h"

using namespace std;
using namespace db07;

Insert_data_node::Insert_data_node(const shared_ptr<Table_definition> &table_definition,
                                   unique_ptr<vector<shared_ptr<Row>>> rows) :
        _table_definition(table_definition), _rows(move(rows)) {
    _position = _rows->begin();
}

bool Insert_data_node::fetch_next() {
    return _position != _rows->end();
}

std::shared_ptr<Row> Insert_data_node::next() {
    return *_position++;
}

shared_ptr<Table_definition> Insert_data_node::definition() const {
    return _table_definition;
}

