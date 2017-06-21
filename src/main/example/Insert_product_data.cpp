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

    unique_ptr<vector<shared_ptr<Row>>> rows(new vector<shared_ptr<Row>>());

    for (int i = 1; i <= 100; ++i) {
        shared_ptr<vector<shared_ptr<Value>>> values(new vector<shared_ptr<Value>>());
        values->push_back(unique_ptr<Value>(new Int_value(i)));
		values->push_back(unique_ptr<Value>(new Varchar_value("Screw #" + to_string(i))));
        values->push_back(unique_ptr<Value>(new Varchar_value("Holds " + to_string(i)  + " things together.")));
        values->push_back(unique_ptr<Value>(new Int_value(10000 - i * 10 - i)));

        rows->push_back(unique_ptr<Row>(new Row(values)));
    }

    unique_ptr<Plan_node> source(new Insert_data_node(table_definition, move(rows)));

    unique_ptr<Insert_plan> plan(new Insert_plan(move(source), products_table));

    return plan;
}
