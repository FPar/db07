#include "Table_scan.h"

using namespace std;
using namespace db07;

static bool called = false;

bool Table_scan::has_next() {
    if (called) {
        called = false;
        return false;
    } else {
        called = true;
        return true;
    }
}

shared_ptr<Row> Table_scan::next() {
    // TODO: WE NEED AN ITERATOR FOR ALL NODES
    auto row = _table->data().indexSeek(1);
    return *row;
}
