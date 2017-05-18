#ifndef DESTINATION_RECEIVER_H
#define DESTINATION_RECEIVER_H

#include "storage_engine/Attribute.h"
#include "storage_engine/Tuple.h"

namespace db07 {
    class Destination_receiver {
    private:
        Tuple_description *m_description;

        void horizontal_line();

    public:
        Destination_receiver(Tuple_description *description);
        ~Destination_receiver();

        void receive(Tuple &tuple);
    };
}

#endif // !EXECUTOR_DESTINATION_H
