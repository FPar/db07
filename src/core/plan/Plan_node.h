#ifndef PLAN_NODE_H
#define PLAN_NODE_H

#include <memory>
#include <storage_engine/Row.h>

namespace db07 {
    class Plan_node {
    public:
        virtual ~Plan_node() = default;

        virtual bool fetch_next() = 0;

        virtual std::shared_ptr<Row> next() = 0;
    };
}

#endif
