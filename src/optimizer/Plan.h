#ifndef PLAN_H
#define PLAN_H

#include "control/Destination_receiver.h"

namespace db07 {
    class Plan {
    public:
        virtual void execute(Destination_receiver &destination) = 0;
    };
}

#endif // !PLAN_H