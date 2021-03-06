#ifndef INT_VALUE_H
#define INT_VALUE_H

#include <storage_engine/types/Types.h>
#include "Value.h"

namespace db07 {
    class Int_value : public Value {
    private:
        int _data;

    public:
        Int_value(int data) : _data(data) {};

        int data() {
            return _data;
        }

        Type *type() const override {
            return &Types::Int_type;
        }

        double compare(const Value &to) override;

        std::string to_string() override;
    };
}

#endif
