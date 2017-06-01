#include "Varchar_value.h"

#include "storage_engine/types/Types.h"

using namespace db07;

Type* Varchar_value::type()
{
    return &Types::Varchar_type;
}

int Varchar_value::compare(Value& to)
{
    Varchar_value& varchar_to = static_cast<Varchar_value&>(to);
    return _data.compare(varchar_to._data);
}