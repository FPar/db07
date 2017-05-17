#ifndef PLAN_H
#define PLAN_H

#include "control/Destination_receiver.h"

namespace db07 {
    class Plan {
    public:
        void execute(Destination_receiver &destination);
    };
}

#endif // !PLAN_H