#include "Global_object_store.h"

using namespace std;
using namespace db07;

Global_object_store::Global_object_store() {
    string name("tables");
    _tables = new Object_store<Table>(name);
}