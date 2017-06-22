#ifndef QUERY_PLAN_H
#define QUERY_PLAN_H

#include <control/Destination_receiver.h>
#include <plan/Plan_node.h>
#include <plan/Projection.h>
#include "Plan.h"

namespace db07 {
    class Select_plan : public Plan {
    public:
        Select_plan(std::unique_ptr<Destination_receiver> receiver, std::unique_ptr<Plan_node> root) :
            _receiver(move(receiver)), _root(move(root)) {
        }

        Select_plan(std::unique_ptr<Destination_receiver> receiver, std::unique_ptr<Plan_node> root, std::unique_ptr<Projection> projection) :
            _receiver(move(receiver)), _root(move(root)), _projection(move(projection)) {
        }

        void execute() override;

    private:
        std::unique_ptr<Destination_receiver> _receiver;
        std::unique_ptr<Plan_node> _root;
        std::unique_ptr<Projection> _projection;
    };
}

#endif
