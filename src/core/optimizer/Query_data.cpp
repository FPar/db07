#include <list>
#include "optimizer/Query_condition.h"
#include "optimizer/Query_data.h"


namespace db07 {

    const Query_type Query_data::getQuery_type() const {
        return _queryType;
    }

    std::string Query_data::getTableName() {
        return _tableName;
    }

    std::vector<std::string> Query_data::getPrimaryKeys() {
        return _primaryKey;
    }

    std::vector<Query_condition> Query_data::getConditions() const {
        return _conditions;
    }

    std::vector<Value*> Query_data::getColumnValues() {
        return _values;

    }

    const std::vector<std::string> &Query_data::getColumnName() const {
        return _columnName;
    }
}