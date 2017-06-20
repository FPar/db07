#ifndef DB07_QUERY_DATA_H
#define DB07_QUERY_DATA_H

#include <string>
#include <vector>
#include "Query_condition.h"
#include "Query_type.h"

namespace db07 {
    class Query_data {

    private:
        /**Query_type defines the type of the query.*/
        const Query_type _queryType;
        /**String table on where the query will be executed.*/
        const std::string _tableName;
        /**String column which is needed for the select statement.*/
        const std::vector<std::string> _columnName;
        /**List of primaryKey for the create statement.*/
        std::vector<std::string> _primaryKey;
        /**List of condition in an query statement.*/
        std::vector<Query_condition> _conditions;
        /**
         * List of pair of column name and value.
         * Pairing column name with data type,
         * or insert/update a value in a column.
         */
        std::vector<Value*> _values;

    public:

        const Query_type getQuery_type() const;

        std::string getTableName();

        std::vector<std::string> getPrimaryKeys();

        std::vector<Query_condition> getConditions() const;

        std::vector<Value*> getColumnValues();

        const std::vector<std::string> &getColumnName() const;

        Query_data(const Query_type queryType, const std::string &tableName, const std::vector<std::string> &columnName,
                   const std::vector<std::string> &primaryKey, std::vector<Query_condition> &conditions,
                   std::vector<Value*> &values) : _queryType(queryType),
                                                 _tableName(tableName),
                                                 _columnName(columnName),
                                                 _primaryKey(primaryKey),
                                                 _conditions(conditions),
                                                 _values(values) {}

    };

}

#endif //DB07_QUERY_DATA_Hs
