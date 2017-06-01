#include "Row.h"

#include <cassert>

using namespace std;
using namespace db07;

Value* const Row::get(const string &field) const
{
    int index = 0;
    for (auto i = _description->cbegin(); i != _description->cend(); ++i) {
        if ((*i).name() == field) {
            return _values.at(index);
        }
    }
    assert(0);
}

int Row::compare_field(const string &field, const Value &to) const
{
    Value* value = get(field);
    return value->compare(to);
}