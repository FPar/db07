#include <stdexcept>
#include "Table_definition.h"

using namespace db07;

int Table_definition::column_id(std::string &name) const {
    int index = 0;
    for (auto i = _columns.cbegin(); i != _columns.cend(); ++i) {
        if ((*i).name() == name) {
            return index;
        }
    }
    throw std::runtime_error("Table does not contain given field.");
}
