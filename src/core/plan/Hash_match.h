#ifndef HASH_MATCH_H
#define HASH_MATCH_H

#include <memory>
#include <map>
#include <vector>
#include "Plan_node.h"
#include <storage_engine/Row.h>

namespace db07 {
    class Hash_match : public Plan_node {
    public:
        bool fetch_next() override;

        std::shared_ptr<Row> next() override;

    private:
        std::map<int, std::vector<std::shared_ptr<Row>>> _map;
    };
}

#endif
