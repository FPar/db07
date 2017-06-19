#include <storage_engine/Table_definition_builder.h>
#include <storage_engine/types/Types.h>
#include "Create_products_table.h"

using namespace std;
using namespace db07;

unique_ptr<Create_table_command> Create_products_table::command() {
    Table_definition_builder builder;
    builder.add_column("id", Types::Int_type);
    builder.add_column("name", Types::Varchar_type);
    builder.add_column("description", Types::Varchar_type);
    builder.add_column("stock", Types::Int_type);
    shared_ptr<Table_definition> def(new Table_definition(builder.get()));

    std::unique_ptr<db07::Create_table_command> command(new db07::Create_table_command("products", def));

    return command;
}
