#ifndef DB07_QUERY_CONDITION_H
#define DB07_QUERY_CONDITION_H

#include <string>
#include <storage_engine/values/Value.h>
#include <storage_engine/values/Int_value.h>
#include <memory>

namespace db07 {
    class Query_condition {
    private:
        /**String column on which the condition es executed.*/
        std::string _column;
        /**String operation, for example equals or greater than.*/
        std::string _operation;
        /**Value value on which the operation is compared.*/
        Value* _value;


    private:
        /**Condition pointer to the next condition, if it exist.*/
        Query_condition *_nextCondition;
        /**String boolean operator between the next condition.*/
        std::string _booleanOperator;

    public:

        std::string &getColumn();

        std::string &getOperation();

        Value* getValue();

        Query_condition *getNextCondition();

        std::string &getBooleanOperator();

        Query_condition(const std::string &_column, const std::string &_operation,
                        Value* _value, Query_condition *_nextCondition,
                        const std::string &_booleanOperator) :
                _column(_column),
                _operation(_operation),
                _value(_value),
                _nextCondition(_nextCondition),
                _booleanOperator(_booleanOperator) {}

    };


}

#endif //DB07_QUERY_CONDITION_H
