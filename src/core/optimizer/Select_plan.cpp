#include "optimizer/Select_plan.h"

using namespace db07;

void Select_plan::execute() {
    while(_root->has_next()) {
        _receiver->receive(*_root->next());
    }
}
