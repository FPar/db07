#include <memory>
#include "optimizer/Query_condition.h"

namespace db07 {
     std::string &Query_condition::getColumn()  {
        return _column;
    }

     std::string &Query_condition::getOperation()  {
        return _operation;
    }

    Value* Query_condition::getValue()  {
        return _value;
    }

     Query_condition *Query_condition::getNextCondition()  {
        return _nextCondition;
    }

     std::string &Query_condition::getBooleanOperator()  {
        return _booleanOperator;
    }

    void Query_condition::set_column(const std::string &_column) {
        Query_condition::_column = _column;
    }

    void Query_condition::set_operation(const std::string &_operation) {
        Query_condition::_operation = _operation;
    }

    void Query_condition::set_value(Value *_value) {
        Query_condition::_value = _value;
    }

    void Query_condition::set_nextCondition(Query_condition *_nextCondition) {
        Query_condition::_nextCondition = _nextCondition;
    }

    void Query_condition::set_booleanOperator(const std::string &_booleanOperator) {
        Query_condition::_booleanOperator = _booleanOperator;
    }


}

