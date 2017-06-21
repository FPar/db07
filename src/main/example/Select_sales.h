#ifndef DB07_SELECT_PRODUCT_BY_ID_H
#define DB07_SELECT_PRODUCT_BY_ID_H

#include <optimizer/Select_plan.h>
#include <storage_engine/Global_object_store.h>

class Select_sales {
public:
    std::unique_ptr<db07::Select_plan> plan(db07::Global_object_store &global_object_store);
};


#endif
