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
        Query_type _queryType;
        /**String table on where the query will be executed.*/
        std::vector<std::string> _tableName;
        /**String column which is needed for the select statement.*/
         std::vector<std::string> _columnNames;
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

        Query_type getQuery_type() const;

        std::vector<std::string> &getTableName();

        std::vector<std::string> &getPrimaryKeys();

        std::vector<Query_condition> &getConditions();

        std::vector<Value*> &getColumnValues();

        std::vector<std::string> &getColumnNames();

        void set_queryType(Query_type _queryType);

    };

}

#endif //DB07_QUERY_DATA_Hs
