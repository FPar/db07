#include "Create_table_command.h"

using namespace std;
using namespace db07;

void Create_table_command::execute(Global_object_store &global_object_store) {
    shared_ptr<Table> table(new Table(_name, _table_definition));
    global_object_store.tables().add(table);
}
