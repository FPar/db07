#include "Int_value.h"

#include "storage_engine/types/Types.h"

using namespace db07;

Type* Int_value::type()
{
    return &Types::Int_type;
}

int Int_value::compare(Value& to)
{
    Int_value& to_int = static_cast<Int_value&>(to);
    return to_int._data - _data;
}