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




}

