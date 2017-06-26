#include <plan/Table_scan.h>
#include <plan/matching/Greater_equals_condition.h>
#include <plan/matching/Less_equals_condition.h>
#include <plan/matching/And_condition.h>
#include <storage_engine/values/Int_value.h>
#include <plan/Hash_match.h>
#include "Select_sales.h"

using namespace std;
using namespace db07;

std::unique_ptr<db07::Select_plan> Select_sales::plan(db07::Global_object_store &global_object_store) {
    shared_ptr<Table> products_table = global_object_store.tables().find("product");
    shared_ptr<Table> sales_table = global_object_store.tables().find("sales");

    unique_ptr<Condition> product_cond(
        new And_condition(unique_ptr<Condition>(new Greater_equals_condition(0, unique_ptr<Value>(new Int_value(3)))),
            unique_ptr<Condition>(new Less_equals_condition(0, unique_ptr<Value>(new Int_value(11))))));
    unique_ptr<Plan_node> product_node(new Table_scan(products_table, move(product_cond)));

    unique_ptr<Plan_node> sales_node(new Table_scan(sales_table));

    unique_ptr<Plan_node> join_node(
        new Hash_match(move(product_node), move(sales_node),
        (unsigned int)products_table->definition()->column_id("product_id"),
            (unsigned int)sales_table->definition()->column_id("sales_product_id")));

    vector<string> proj_columns{ "product_id", "product_name", "product_price", "sales_cust_id", "sales_cust_name", "sales_units" };
    unique_ptr<Projection> proj(new Projection(*join_node->definition(), proj_columns));

    unique_ptr<Destination_receiver> destination_receiver(new Destination_receiver());

    unique_ptr<Select_plan> plan(new Select_plan(move(destination_receiver), move(join_node), move(proj)));
    return plan;
}
