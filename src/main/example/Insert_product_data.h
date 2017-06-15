#ifndef INSERT_PRODUCT_DATA_H
#define INSERT_PRODUCT_DATA_H

#include <storage_engine/Global_object_store.h>
#include <optimizer/Insert_plan.h>

class Insert_product_data {
public:
    std::unique_ptr<db07::Insert_plan> plan(db07::Global_object_store &global_object_store);
};


#endif
