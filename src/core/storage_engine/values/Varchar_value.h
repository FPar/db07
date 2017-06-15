#ifndef VARCHAR_VALUE_H
#define VARCHAR_VALUE_H

#include <string>

#include "Value.h"

namespace db07 {
    class Varchar_value : public Value {
    private:
        std::string _data;

    public:
        Varchar_value(const std::string &data) : _data(data) {};

        Type *type();

        int compare(const Value &to);
    };
}

#endif // !VARCHAR_VALUE_H
