#include "Row.h"

using namespace std;
using namespace db07;

shared_ptr<Value> Row::get(unsigned int field) const {
    return _values->at(field);
}
