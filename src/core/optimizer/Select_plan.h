#ifndef QUERY_PLAN_H
#define QUERY_PLAN_H

#include "control/Destination_receiver.h"
#include "Plan.h"
#include "plan/Plan_node.h"

namespace db07 {
    class Select_plan : public Plan {
    public:
        Select_plan(std::unique_ptr<Destination_receiver> receiver, std::unique_ptr<Plan_node> root) :
                _receiver(move(receiver)), _root(move(root)) {
        }

        void execute() override;

    private:
        std::unique_ptr<Destination_receiver> _receiver;
        std::unique_ptr<Plan_node> _root;
    };
}

#endif
