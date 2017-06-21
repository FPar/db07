#include "Table_scan.h"

using namespace std;
using namespace db07;

bool Table_scan::fetch_next() {
    do {
        if (it != nullptr) {
            ++*it;
        } else {
            it = std::unique_ptr<Btree::iterator>(new Btree::iterator(_table->data().begin()));
        }
    } while (*it != _table->data().end() && !_condition->fulfil(***it));
    return *it != _table->data().end();
}

shared_ptr<Row> Table_scan::next() {
    auto row = **it;
    return row;
}

shared_ptr<Table_definition> Table_scan::definition() const {
    return _table->definition();
}
