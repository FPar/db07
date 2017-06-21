#include <iostream>
#include "Destination_receiver.h"

using namespace std;
using namespace db07;

Destination_receiver::Destination_receiver(const std::shared_ptr<Table_definition> &description) :
        _description(description) {
    horizontal_line();

    for (auto i = _description->columns().cbegin(); i != _description->columns().cend(); ++i) {
        cout << '|' << i->name();
    }
    cout << "|\n";

    horizontal_line();
}

Destination_receiver::~Destination_receiver() {
    horizontal_line();
}

void Destination_receiver::receive(Row &row) {
    for (size_t i = 0; i < _description->columns().size(); ++i) {
        cout << '|' << row.get(i).to_string();
    }
    cout << "|\n";
}

void Destination_receiver::horizontal_line() {
    for (auto i = _description->columns().cbegin(); i != _description->columns().cend(); ++i) {
        cout << '+';
        for (size_t k = 0; k < i->name().length(); ++k) {
            cout << '-';
        }

    }
    cout << "+\n";
}