#include <plan/matching/Comparing_condition.h>
#include <plan/matching/Equals_condition.h>
#include <plan/matching/Greater_condition.h>
#include <plan/Table_scan.h>
#include <plan/matching/Less_equals_condition.h>
#include <plan/matching/Greater_equals_condition.h>
#include <plan/matching/Less_condition.h>
#include <plan/matching/Unequals_condition.h>
#include <plan/Insert_data_node.h>
#include <plan/matching/And_condition.h>
#include <plan/matching/Or_condition.h>
#include "Build_Plan.h"

using namespace std;

namespace db07 {


    void Build_Plan::build(Query_data &data) {
        const Query_type type = data.getQuery_type();

        switch (type) {
            case SELECT:
                planSelect(data);
            case INSERT:
                planInsert(data);
                break;
            case DELETE:
                break;
            case UPDATE:
                break;
            case CREATE:
                break;
        }
    }

    Insert_plan Build_Plan::planInsert(Query_data &data) {
        shared_ptr<Table> products_table = _global_object_store->tables().find(data.getTableName().front());
        shared_ptr<Table_definition> table_definition(products_table->definition());
        vector<Value *> values = (vector<Value *> &&) data.getColumnValues();

        unique_ptr<vector<shared_ptr<Row>>> rows(new vector<shared_ptr<Row>>());
        shared_ptr<vector<shared_ptr<Value>>> valueRow(new vector<shared_ptr<Value>>());
        for (vector<Value *>::iterator it = values.begin(); it != values.end(); ++it) {
            valueRow->push_back(unique_ptr<Value>(it.operator*()));
        }
        rows->push_back(unique_ptr<Row>(new Row(valueRow)));

        unique_ptr<Plan_node> source(new Insert_data_node(table_definition, move(rows)));
        Insert_plan plan(Insert_plan(move(source), products_table));
        return plan;
    }

    Select_plan Build_Plan::planSelect(Query_data &data) {
        shared_ptr<Table> table = _global_object_store->tables().find(data.getTableName().front());
        std::unique_ptr<Condition> cond = planCondition(data);
        unique_ptr<Plan_node> table_scan(new Table_scan(table, move(cond)));
        Destination_receiver receiver(table->definition());
        Select_plan select_plan(unique_ptr<Destination_receiver>(_receiver), move(table_scan));
        return select_plan;
    }

    std::unique_ptr<Condition> Build_Plan::planCondition(Query_data &data) {
        vector<Query_condition> &condition = data.getConditions();
        vector<string> &booleanOperations = data.get_booleanOperations();
        unique_ptr<Condition> current = getOperation(condition[0], data);
        for (int i = 0; i < condition.size(); i++) {
            if (booleanOperations[i] == "and") {
                current = unique_ptr<Condition>(new And_condition(&*current, &*getOperation(condition[i + 1], data)));
            } else if (booleanOperations[i] == "or") {
                current = unique_ptr<Condition>(new Or_condition(&*current, &*getOperation(condition[i + 1], data)));
            }
        }
        return current;
    }

    unique_ptr<Condition>
    Build_Plan::getOperation(Query_condition &condition, Query_data &data) {
        int col = _global_object_store->tables().find(data.getTableName().front())->definition()->column_id(
                condition.getColumn());

        string &op = condition.getOperation();
        if (op == "=") {
            return unique_ptr<Condition>(new Equals_condition(col, unique_ptr<Value>(condition.getValue())));
        }
        if (op == ">") {
            return unique_ptr<Condition>(new Greater_condition(col, unique_ptr<Value>(condition.getValue())));
        }
        if (op == "<=") {
            return unique_ptr<Condition>(new Less_equals_condition(col, unique_ptr<Value>(condition.getValue())));
        }
        if (op == "<=") {
            return unique_ptr<Condition>(new Greater_equals_condition(col, unique_ptr<Value>(condition.getValue())));
        }
        if (op == "<") {
            return unique_ptr<Condition>(new Less_condition(col, unique_ptr<Value>(condition.getValue())));
        }
        if (op == "!=") {
            return unique_ptr<Condition>(new Unequals_condition(col, unique_ptr<Value>(condition.getValue())));
        }
    }
}

