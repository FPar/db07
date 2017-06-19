#include <plan/matching/Comparing_condition.h>
#include <plan/matching/Equals_condition.h>
#include <plan/matching/Greater_condition.h>
#include <plan/Table_scan.h>
#include <plan/matching/Less_equals_condition.h>
#include <plan/matching/Greater_equals_condition.h>
#include <plan/matching/Less_condition.h>
#include <plan/matching/Unequals_condition.h>
#include "Build_Plan.h"

using namespace std;

namespace db07 {


    void Build_Plan::build(Query_data &data) {
        const Query_type type = data.getQuery_type();

        switch (type) {
            case SELECT:
                planSelect(data);
        }
    }

    void Build_Plan::planSelect(Query_data &data) {
        shared_ptr<Table> table = _global_object_store->tables().find(data.getTableName());
        std::unique_ptr<Condition> cond = planCondition(data);
        Table_scan table_scan(table, move(cond));

    }

    std::unique_ptr<Condition> Build_Plan::planCondition(Query_data &data) {
        std::vector<Query_condition> conditions = data.getConditions();
        for (std::vector<Query_condition>::iterator it = conditions.begin(); it != conditions.end(); ++it) {
            Query_condition next = *it->getNextCondition();
            //TODO überarbeiten
            if (next.getNextCondition() == NULL) {
                return getOperation(next.getOperation(), next, data);
            } else {

            }

        }
    }

    unique_ptr<Condition>
    Build_Plan::getOperation(std::string &op, Query_condition &condition, Query_data &data) {
        int col = _global_object_store->tables().find(data.getTableName())->definition()->column_id(
                condition.getColumn());

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

