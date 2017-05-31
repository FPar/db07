#ifndef QUERY_PLAN_H
#define QUERY_PLAN_H

#include "control/Destination_receiver.h"
#include "optimizer/Plan.h"
#include "optimizer/Plan_node.h"

namespace db07 {
    class Select_plan : public Plan {
    private:
        Destination_receiver *m_receiver;
        Plan_node *m_root;

    public:
        Select_plan(Destination_receiver *receiver, Plan_node *root) :
            m_receiver(receiver), m_root(root) { }

        void execute();
    };
}

#endif // !QUERY_PLAN_H
