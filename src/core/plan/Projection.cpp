#include "Projection.h"

using namespace std;
using namespace db07;

Projection::Projection(Table_definition& input, vector<string>& columns)
{
    vector<Column> cols;
    for (auto column_name : columns)
    {
        int pos = input.column_id(column_name);
        _columns.push_back(pos);
        cols.push_back(input.columns()[pos]);
    }
    _definition = shared_ptr<Table_definition>(new Table_definition(cols));
}

shared_ptr<Row> Projection::project(Row& row)
{
    shared_ptr<vector<shared_ptr<Value>>> values(new vector<shared_ptr<Value>>());
    for (auto pos : _columns) {
        auto value = row.get(pos);
        values->push_back(value);
    }
    shared_ptr<Row> result(new Row(values));
    return result;
}
