#ifndef HASH_MATCH_H
#define HASH_MATCH_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "Plan_node.h"
#include <storage_engine/Table.h>

namespace db07 {
    class Hash_match : public Plan_node {
    public:
        Hash_match(std::unique_ptr<Plan_node> a, std::unique_ptr<Plan_node> b, unsigned int col_key_a,
                   unsigned int col_key_b);

        bool fetch_next() override;

        std::shared_ptr<Row> next() override;

        std::shared_ptr<Table_definition> definition() const override;

    private:
        std::shared_ptr<Table_definition> _definition;

        std::unique_ptr<Plan_node> b;
        unsigned int col_key_b;

        std::unordered_multimap<int, std::shared_ptr<Row>> matching;
        Row *next_row;
    };
}

#endif
