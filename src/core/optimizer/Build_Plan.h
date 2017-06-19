#ifndef DB07_BUILD_PLAN_H
#define DB07_BUILD_PLAN_H

#include <memory>
#include <storage_engine/Global_object_store.h>
#include "Query_condition.h"
#include "Query_data.h"

namespace db07 {
    class Build_Plan {
    public:
        explicit Build_Plan(std::shared_ptr<Global_object_store> &global_object_store) : _global_object_store(
                global_object_store) {
        }

    private:
        std::shared_ptr<Global_object_store> _global_object_store;

        void planSelect(Query_data& data);

        void build(Query_data& data);

        std::unique_ptr<Condition> planCondition(Query_data& data);


        std::unique_ptr<Condition>
        getOperation(std::string& op, Query_condition& condition, Query_data& data);
    };
}


#endif //DB07_BUILD_PLAN_H