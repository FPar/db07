#include "Table_scan.h"

using namespace std;
using namespace db07;

bool Table_scan::has_next() {
    return it != _table->data().end();
}

shared_ptr<Row> Table_scan::next() {
    auto row = *it;
    ++it;
    return row;
}
