#include "Row.h"

using namespace std;
using namespace db07;

Value* const Row::get(string &field) const
{
    int index = 0;
    for (auto i = _description->cbegin(); i != _description->cend(); ++i) {
        if ((*i).name() == field) {
            return _values.at(index);
        }
    }
}

int Row::compare_field(string &field, Value &to) const
{
    return 0;
}