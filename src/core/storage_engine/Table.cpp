#include <storage_engine/values/Int_value.h>
#include "Table.h"

using namespace db07;

void Table::insert(Row *row) {
    Int_value *id = static_cast<Int_value *>(row->get(0));
    _data.insert(id->data(), row);
}
