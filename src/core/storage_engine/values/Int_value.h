#ifndef INT_VALUE_H
#define INT_VALUE_H

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

        Type *type() const;

        int compare(const Value &to);

        std::string to_string() override;
    };
}

#endif
