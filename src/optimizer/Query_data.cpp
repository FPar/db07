#include <list>
#include "Query_condition.h"
#include "Query_data.h"

using namespace std;

namespace db07 {

    string Query_data::getTableName() {
        return std::string();
    }

    string Query_data::getColumnName() {
        return std::string();
    }

    list<string> Query_data::getPrimaryKeys() {
        return list<string, allocator<string>>();
    }

    list<Query_condition> Query_data::getConditions() {
        return list<Query_condition, allocator<Query_condition>>();
    }

    list<pair<string, string>> Query_data::getColumnValues() {
        return list<pair<string, string>, allocator<pair<string, string>>>();
    }
}