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


    unique_ptr<Plan> Build_Plan::build(Query_data &data) {
        const Query_type type = data.getQuery_type();

        switch (type) {
            case SELECT:
                return planSelect(data);
            case INSERT:
                return planInsert(data);
            case DELETE:
                break;
            case UPDATE:
                break;
            case CREATE:
                break;
        }
        return unique_ptr<Plan>();
    }


    unique_ptr<Plan> Build_Plan::planInsert(Query_data &data) {
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
        return unique_ptr<Plan>(new Insert_plan(move(source), products_table));
    }

    /**
     * This method creates the select plan.
     * @param data Query data needed to get the select query informations
     * @return unique pointer of a plan
     */
    unique_ptr<Plan> Build_Plan::planSelect(Query_data &data) {
        shared_ptr<Table> table = _global_object_store->tables().find(data.getTableName().front());
        std::unique_ptr<Condition> cond = planCondition(data);


        Table_scan *ts;
        if (cond != nullptr)
            ts = new Table_scan(table, move(cond));
        else
            ts = new Table_scan(table);

        unique_ptr<Plan_node> table_scan(ts);
        unique_ptr<Projection> proj = planProjection(*table_scan, data);
        unique_ptr<Plan> select_plan(
                new Select_plan(unique_ptr<Destination_receiver>(new Destination_receiver()), move(table_scan),
                                move(proj)));
        return select_plan;
    }

    /**
     * This method creates the projection.
     * @param table_scan Table_scan contains the table definition needed for the projection
     * @param data Query data contains the column names needed for the projection
     * @return  unique pointer of a projection
     */
    unique_ptr<Projection> Build_Plan::planProjection(Plan_node& table_scan, Query_data &data) {
        shared_ptr<Table> products_table = _global_object_store->tables().find(data.getTableName().front());
        vector<string> proj_columns = (vector<string> &&) data.getColumnNames();
        unique_ptr<Projection> proj(new Projection(*table_scan.definition(), proj_columns));
        return proj;
    }

    /**
     * This method plans the conditions.
     * Goes to the list of conditions and connects them with boolean operator if available
     * @param data Data containing the vector of conditions the a vector of boolean operations
     * @return  unique pointer of a root condition
     */
    unique_ptr<Condition> Build_Plan::planCondition(Query_data &data) {
        vector<Query_condition> &condition = data.getConditions();

        if (condition.empty())
            return unique_ptr<Condition>();

        vector<string> &booleanOperations = data.get_booleanOperations();
        unique_ptr<Condition> current = getOperation(condition[0], data);
        for (unsigned int i = 0; i < condition.size(); i++) {
            if (!booleanOperations.empty()) {
                if (booleanOperations[i] == "and") {
                    current = unique_ptr<Condition>(
                            new And_condition(move(current), move(getOperation(condition[i + 1], data))));
                } else if (booleanOperations[i] == "or") {
                    current = unique_ptr<Condition>(
                            new Or_condition(move(current), move(getOperation(condition[i + 1], data))));
                }
            }
        }
        return current;
    }

    /**
     * This method creates a condition from the evaluation informations.
     * @param condition Query condition containing the compare operator and the value on which a column gets compared
     * @param data Query data holding the table name, which is needed to extract the column number
     * @return unique pointer of an condition
     */
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
        return unique_ptr<Condition>();
    }
}

