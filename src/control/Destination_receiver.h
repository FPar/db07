#ifndef DESTINATION_RECEIVER_H
#define DESTINATION_RECEIVER_H

#include "storage_engine/Attribute.h"

namespace db07 {
    class Destination_receiver {
    public:
        bool receive_slot();
        void startup(Tuple_description &tuple_desc);
    };
}

#endif // !EXECUTOR_DESTINATION_H
