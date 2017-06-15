#include <storage_engine/values/Int_value.h>
#include "Table.h"

using namespace std;
using namespace db07;

void Table::insert(Row &row) {
    auto &id = reinterpret_cast<Int_value &>(*row.get(0));
    _data.insert(id.data(), &row);
}
