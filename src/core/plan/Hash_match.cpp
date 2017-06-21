#include <storage_engine/values/Int_value.h>
#include "Hash_match.h"

using namespace std;
using namespace db07;

Hash_match::Hash_match(const shared_ptr<Table>& a, const shared_ptr<Table>& b, int col_key_a, int col_key_b) :
    b(b), col_key_b(col_key_b)
{
    for (auto it = a->data().begin(); it != a->data().end(); ++it) {
        auto& key = static_cast<Int_value&>((*it)->get(col_key_a));
        auto match = matching.find(key.data());
        if (match == matching.end()) {
            matching.insert(make_pair(key.data(), vector<std::shared_ptr<Row>>()));
            match = matching.find(key.data());
        }
    }
}

bool Hash_match::fetch_next()
{
    return false;
}

shared_ptr<Row> Hash_match::next()
{
    return std::shared_ptr<Row>();
}
