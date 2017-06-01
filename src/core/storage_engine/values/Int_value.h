#ifndef INT_VALUE_H
#define INT_VALUE_H

#include "Value.h"

namespace db07 {
    class Int_value : public Value {
    private:
        int _data;

    public:
        Int_value(int data) : _data(data) {};
        Type* type();
        int compare(const Value & to);
    };
}

#endif // !INT_VALUE_H