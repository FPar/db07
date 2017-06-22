#include <storage_engine/values/Int_value.h>
#include "Hash_match.h"

using namespace std;
using namespace db07;

Hash_match::Hash_match(unique_ptr<Plan_node> a, unique_ptr<Plan_node> b,
                       unsigned int col_key_a, unsigned int col_key_b) :
        _definition(new Table_definition(*a->definition(), *b->definition())), b(move(b)), col_key_b(col_key_b) {
    while (a->fetch_next()) {
        auto next = a->next();
        auto key = static_pointer_cast<Int_value>(next->get(col_key_a));
        matching.insert(make_pair(key->data(), next));
    }
}

bool Hash_match::fetch_next() {
    while (b->fetch_next()) {
        shared_ptr<Row> next = b->next();
        auto key = static_pointer_cast<Int_value>(next->get(col_key_b));
        auto match = matching.find(key->data());
        if (match != matching.end()) {
            shared_ptr<vector<shared_ptr<Value>>> values(new vector<shared_ptr<Value>>);
            values->insert(values->end(), match->second->values()->begin(), match->second->values()->end());
            values->insert(values->end(), next->values()->begin(), next->values()->end());
            next_row = new Row(values);
            return true;
        }
    }
    return false;
}

shared_ptr<Row> Hash_match::next() {
    return std::shared_ptr<Row>(next_row);
}

shared_ptr<Table_definition> Hash_match::definition() const {
    return _definition;
}
