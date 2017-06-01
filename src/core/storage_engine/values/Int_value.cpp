#include "Int_value.h"

#include "storage_engine/types/Types.h"

using namespace db07;

Type* Int_value::type() {
    return &Types::Int_type;
}