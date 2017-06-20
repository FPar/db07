#include "Insert_plan.h"

using namespace std;
using namespace db07;

void Insert_plan::execute() {
    while (_source->fetch_next()) {
        std::shared_ptr<Row> current = _source->next();
        _target->insert(current);
        ++_rows_inserted;
    }
}
