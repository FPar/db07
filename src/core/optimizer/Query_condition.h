#ifndef DB07_QUERY_CONDITION_H
#define DB07_QUERY_CONDITION_H

#include <string>
#include <storage_engine/values/Value.h>
#include <storage_engine/values/Int_value.h>
#include <memory>
#include <storage_engine/values/Varchar_value.h>

namespace db07 {
    class Query_condition {
    private:
        /**String column on which the condition es executed.*/
        std::string _column;
        /**String operation, for example equals or greater than.*/
        std::string _operation;
        /**Value value on which the operation is compared.*/
        Value *_value;


    public:

        std::string &getColumn();

        std::string &getOperation();

        void set_column(const std::string &_column);

        Value *getValue();

        void set_value(Value *_value);

        void set_operation(const std::string &_operation);


    };


}

#endif //DB07_QUERY_CONDITION_H
