#include <list>
#include "optimizer/Query_condition.h"
#include "optimizer/Query_data.h"

using namespace std;

namespace db07 {

    const Query_type Query_data::getQuery_type() const {
        return _queryType;
    }

    string Query_data::getTableName() {
        return _tableName;
    }

    list <string> Query_data::getPrimaryKeys() {
        return _primaryKey;
    }

    list <Query_condition> Query_data::getConditions() {
        return _conditions;
    }

    list <pair<string, string>> Query_data::getColumnValues() {
        return _columns2value;

    }

    const list <string> &Query_data::getColumnName() const {
        return _columnName;
    }

    Query_data::Query_data(const string &tableName, const list <string> &columnName, const list <string> &primaryKey,
                           const list <Query_condition> &conditions, const list <pair<string, string>> &columns2value,
                           const Query_type &queryType) {

    }

}