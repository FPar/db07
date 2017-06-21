#include "Double_value.h"

using namespace std;
using namespace db07;

double Double_value::compare(const Value &to) {
    const Double_value &to_int = static_cast<const Double_value &>(to);
    return _data - to_int._data;
}

string Double_value::to_string() {
    return std::to_string(_data);
}
