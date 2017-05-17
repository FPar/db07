#ifndef DB07_QUERY_CONDITION_H
#define DB07_QUERY_CONDITION_H

#include <string>

namespace db07 {
    class Query_condition {
    private:
        /**String column on which the condition es executed.*/
        const std::string column;
        /**String operation, for example equals or greater than.*/
        const std::string operation;
        /**String value on which the operation is compared.*/
        const std::string value;
        /**Condition pointer to the next condition, if it exist.*/
        const Query_condition *nextCondition;
        /**String boolean operator between the next condition.*/
        const std::string booleanOperator;

    public:

        const std::string &getColumn() const;

        const std::string &getOperation() const;

        const std::string &getValue() const;

        const Query_condition *getNextCondition() const;

        const std::string &getBooleanOperator() const;

        Query_condition(const std::string &column, const std::string &operation, const std::string &value,
                        const Query_condition *nextCondition, const std::string &booleanOperator) :
                column(column),
                operation(operation),
                value(value),
                nextCondition(nextCondition),
                booleanOperator(booleanOperator) {}

    };


}

#endif //DB07_QUERY_CONDITION_H
