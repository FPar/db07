#ifndef EQUALS_CONDITION_H
#define EQUALS_CONDITION_H

#include "Condition.h"

namespace db07 {
    class Equals_condition : public Condition {
    private:
        const int _field_index;
        const unsigned char *_data;
        const int _data_size;

    public:
        Equals_condition(int field_index, unsigned char *data, int data_size) :
            _field_index(field_index), _data(data), _data_size(data_size)
        {
        }

        bool fulfil(Tuple &tuple) const;
    };
}

#endif // !EQUALS_CONDITION_H
