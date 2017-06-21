#include "Int_value.h"

using namespace std;
using namespace db07;

double Int_value::compare(const Value &to) {
    const Int_value &to_int = static_cast<const Int_value &>(to);
    return _data - to_int._data;
}

string Int_value::to_string() {
    return std::to_string(_data);
}
