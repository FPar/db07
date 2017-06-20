#include "Hash_match.h"

using namespace std;
using namespace db07;

bool Hash_match::fetch_next()
{
    return false;
}

shared_ptr<Row> Hash_match::next()
{
    return std::shared_ptr<Row>();
}
