#include <storage_engine/Table_definition_builder.h>
#include <storage_engine/types/Types.h>
#include "Create_tables.h"

using namespace std;
using namespace db07;

unique_ptr<Create_table_command> Create_tables::product() {
    Table_definition_builder builder;
    builder.add_column("product_id", Types::Int_type);
    builder.add_column("product_name", Types::Varchar_type);
    builder.add_column("product_price", Types::Double_type);
    shared_ptr<Table_definition> def(new Table_definition(builder.get()));

    std::unique_ptr<db07::Create_table_command> command(new db07::Create_table_command("product", def));

    return command;
}

std::unique_ptr<db07::Create_table_command> Create_tables::sales() {
    Table_definition_builder builder;
    builder.add_column("sales_id", Types::Int_type);
    builder.add_column("sales_cust_id", Types::Int_type);
    builder.add_column("sales_cust_name", Types::Varchar_type);
    builder.add_column("sales_product_id", Types::Int_type);
    builder.add_column("sales_units", Types::Int_type);
    shared_ptr<Table_definition> def(new Table_definition(builder.get()));

    std::unique_ptr<db07::Create_table_command> command(new db07::Create_table_command("sales", def));

    return command;
}
