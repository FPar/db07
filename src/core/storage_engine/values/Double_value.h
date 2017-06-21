#ifndef DOUBLE_VALUE_H
#define DOUBLE_VALUE_H

#include <storage_engine/types/Types.h>
#include "Value.h"

namespace db07 {
    class Double_value : public Value {
    private:
        double _data;

    public:
        Double_value(double data) : _data(data) {};

        double data() {
            return _data;
        }

        Type *type() const override {
            return &Types::Double_type;
        };

        double compare(const Value &to) override;

        std::string to_string() override;
    };
}


#endif
