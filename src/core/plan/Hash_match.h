#ifndef HASH_MATCH_H
#define HASH_MATCH_H

#include <memory>
#include <map>
#include <vector>
#include "Plan_node.h"
#include <storage_engine/Table.h>

namespace db07 {
    class Hash_match : public Plan_node {
    public:
        Hash_match(const std::shared_ptr<Table> &a, const std::shared_ptr<Table> &b, int col_key_a, int col_key_b);

        bool fetch_next() override;

        std::shared_ptr<Row> next() override;

    private:
        std::shared_ptr<Table> b;
        int col_key_b;

        std::map<int, std::vector<std::shared_ptr<Row>>> matching;
    };
}

#endif
