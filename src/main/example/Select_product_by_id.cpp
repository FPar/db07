#include <plan/Table_scan.h>
#include <plan/matching/Equals_condition.h>
#include <storage_engine/values/Int_value.h>
#include "Select_product_by_id.h"

using namespace std;
using namespace db07;

unique_ptr<Select_plan> Select_product_by_id::plan(Global_object_store &global_object_store, int id) {
    shared_ptr<Table> products_table = global_object_store.tables().find("products");

    unique_ptr<Destination_receiver> destination_receiver(new Destination_receiver(products_table->definition()));

    unique_ptr<Condition> cond(new Equals_condition(0, unique_ptr<Value>(new Int_value(id))));
    unique_ptr<Plan_node> node(new Table_scan(products_table, move(cond)));

    unique_ptr<Select_plan> plan(new Select_plan(move(destination_receiver), move(node)));
    return plan;
}
