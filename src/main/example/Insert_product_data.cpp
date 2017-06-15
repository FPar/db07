#include <plan/Insert_data_node.h>
#include <storage_engine/Global_object_store.h>
#include <storage_engine/values/Int_value.h>
#include <storage_engine/values/Varchar_value.h>
#include "Insert_product_data.h"

using namespace std;
using namespace db07;

unique_ptr<Insert_plan> Insert_product_data::plan(Global_object_store &global_object_store) {
    shared_ptr<Table> products_table = global_object_store.tables().find("products");
    shared_ptr<Table_definition> table_definition(products_table->definition());

    unique_ptr<vector<unique_ptr<Row>>> rows(new vector<unique_ptr<Row>>());

    vector<Value *> values;
    values.push_back(new Int_value(1));
    values.push_back(new Varchar_value("Screw"));
    values.push_back(new Varchar_value("Holds things together."));
    values.push_back(new Int_value(10));

    rows->push_back(unique_ptr<Row>(new Row(values)));

    unique_ptr<Plan_node> source(new Insert_data_node(table_definition, move(rows)));

    unique_ptr<Insert_plan> plan(new Insert_plan(move(source), products_table));

    return plan;
}
