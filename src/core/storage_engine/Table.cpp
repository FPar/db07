#include <storage_engine/values/Int_value.h>
#include "Table.h"

using namespace std;
using namespace db07;

void Table::insert(std::shared_ptr<Row> &row) {
    auto id = static_pointer_cast<Int_value>(row->get(0));
    _data.insert(id->data(), row);
}
