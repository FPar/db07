#include <iostream>
#include <string>

#include "control/Destination_receiver.h"

using namespace std;
using namespace db07;

void horizontal_line(Tuple_description &tuple_desc) {
    for (auto i = tuple_desc.cbegin(); i != tuple_desc.cend(); ++i) {
        cout << '+';
        for (int k = 0; k < i->name().length(); ++k) {
            cout << '-';
        }

    }
    cout << "+\n";
}

bool db07::Destination_receiver::receive_slot() {
    return false;
}

void db07::Destination_receiver::startup(Tuple_description &tuple_desc) {
    horizontal_line(tuple_desc);

    for (auto i = tuple_desc.cbegin(); i != tuple_desc.cend(); ++i) {
        cout << '|' << i->name();
    }
    cout << "|\n";

    horizontal_line(tuple_desc);
}
