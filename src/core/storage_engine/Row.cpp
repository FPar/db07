#include "Row.h"

using namespace std;
using namespace db07;

const unique_ptr<Value> &Row::get(unsigned int field) const {
    return _values->at(field);
}
