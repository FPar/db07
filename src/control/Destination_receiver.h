#ifndef DESTINATION_RECEIVER_H
#define DESTINATION_RECEIVER_H

namespace db07 {
    class Destination_receiver {
    public:
        virtual bool receive_slot() = 0;
    };
}

#endif // !EXECUTOR_DESTINATION_H
