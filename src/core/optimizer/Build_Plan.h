#ifndef DB07_BUILD_PLAN_H
#define DB07_BUILD_PLAN_H

#include <memory>
#include <storage_engine/Global_object_store.h>
#include <control/Destination_receiver.h>
#include "Query_condition.h"
#include "Query_data.h"
#include "Plan.h"
#include "Select_plan.h"
#include "Insert_plan.h"
#include <plan/matching/Condition.h>

namespace db07 {
    class Build_Plan {
    public:
        explicit Build_Plan(Global_object_store* global_object_store, Destination_receiver *receiver) :
                _global_object_store(global_object_store), _receiver(receiver) {
        }

		std::unique_ptr<Plan> build(Query_data &data);

    private:
		Global_object_store* _global_object_store;

        Destination_receiver *_receiver;

        std::unique_ptr<Insert_plan> planInsert(Query_data &data);

		std::unique_ptr<Select_plan> planSelect(Query_data &data);

        std::unique_ptr<Condition> planCondition(Query_data &data);

        std::unique_ptr<Condition> getOperation(Query_condition &condition, Query_data &data);
    };
}


#endif //DB07_BUILD_PLAN_H
