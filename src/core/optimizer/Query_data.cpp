#include <list>
#include "optimizer/Query_condition.h"
#include "optimizer/Query_data.h"


namespace db07 {

     Query_type Query_data::getQuery_type() const {
        return _queryType;
    }

    std::vector<std::string> &Query_data::getTableName() {
        return _tableName;
    }

    std::vector<std::string> &Query_data::getPrimaryKeys() {
        return _primaryKey;
    }

    Query_condition &Query_data::getConditions()  {
        return _condition;
    }

    std::vector<Value*> &Query_data::getColumnValues() {
        return _values;

    }

     std::vector<std::string> &Query_data::getColumnNames() {
        return _columnNames;
    }

    void Query_data::set_queryType(Query_type _queryType) {
        Query_data::_queryType = _queryType;
    }

    const std::vector<std::string> &Query_data::get_booleanOperations() const {
        return _booleanOperations;
    }
}