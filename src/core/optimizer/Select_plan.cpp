#include "optimizer/Select_plan.h"

using namespace db07;

void Select_plan::execute() {
    while (_root->fetch_next()) {
        auto next = _root->next();
        if (_projection != nullptr) {
            next = _projection->project(*next);
        }
        _receiver->receive(*next);
    }
}
