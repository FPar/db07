#include "Query_condition.h"

namespace db07 {
    const std::string &Query_condition::getColumn() const {
        return column;
    }

    const std::string &Query_condition::getOperation() const {
        return operation;
    }

    const std::string &Query_condition::getValue() const {
        return value;
    }

    const Query_condition *Query_condition::getNextCondition() const {
        return nextCondition;
    }

    const std::string &Query_condition::getBooleanOperator() const {
        return booleanOperator;
    }
}

