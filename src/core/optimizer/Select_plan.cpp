#include "optimizer/Select_plan.h"

using namespace db07;

void Select_plan::execute() {
	_receiver->init(_projection != nullptr ? _projection->definition() : _root->definition());
    while (_root->fetch_next()) {
        auto next = _root->next();
        if (_projection != nullptr) {
            next = _projection->project(*next);
        }
        _receiver->receive(*next);
    }
}
