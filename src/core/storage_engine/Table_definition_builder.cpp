#include "Table_definition_builder.h"

using namespace std;
using namespace db07;

void Table_definition_builder::add_column(string &name, Type &type) {
    Column col(name, type, false);
    _columns.push_back(move(col));
}

Table_definition Table_definition_builder::get() const {
    return Table_definition(_columns);
}
