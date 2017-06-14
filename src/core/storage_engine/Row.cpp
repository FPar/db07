#include "Row.h"
#include <stdexcept>

using namespace std;
using namespace db07;

Row::~Row() {
    for (auto value : _values) {
        delete value;
    }
}

Value *Row::get(unsigned int field) const {
    return _values.at(field);
}
