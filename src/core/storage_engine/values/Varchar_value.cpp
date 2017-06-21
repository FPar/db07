#include "Varchar_value.h"

#include "storage_engine/types/Types.h"

using namespace db07;

Type *Varchar_value::type() const {
    return &Types::Varchar_type;
}

int Varchar_value::compare(const Value &to) {
    const Varchar_value &varchar_to = static_cast<const Varchar_value &>(to);
    return _data.compare(varchar_to._data);
}

std::string Varchar_value::to_string() {
    return _data;
}
