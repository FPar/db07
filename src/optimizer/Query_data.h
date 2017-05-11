#ifndef DB07_QUERY_DATA_H
#define DB07_QUERY_DATA_H

#include <string>
#include <list>
#include "Query_condition.h"
using namespace std;

namespace db07 {
    class Query_data {
    private:
        /**String table on where the query will be executed.*/
        const string tableName;
        /**String column which is needed for the select statement.*/
        const string columnName;
        /**List of primaryKey for the create statement.*/
        list<string> primaryKey;
        /**List of condition in an query statement.*/
        list<Query_condition> conditions;
        /**
         * List of pair of column name and value.
         * Pairing column name with data type,
         * or insert/update a value in a column.
         */
        list<pair<string, string>> columns2value;

    public:
        string getTableName();
        string getColumnName();
        list<string> getPrimaryKeys();
        list<Query_condition> getConditions();
        list<pair<string, string>>getColumnValues();

        Query_data(const string &tableName, const string &columnName, const list<string, allocator<string>> &primarykey,
                   const list<Query_condition, allocator<Query_condition>> &conditions,
                   const list<pair<string, string>, allocator<pair<string, string>>> &columns2value) : tableName(
                tableName), columnName(columnName), primaryKey(primaryKey), conditions(conditions), columns2value(
                columns2value) {}
    };


}

#endif //DB07_QUERY_DATA_H
