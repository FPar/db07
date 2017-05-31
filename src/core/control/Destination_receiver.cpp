#include <iostream>
#include <string>

#include "control/Destination_receiver.h"

using namespace std;
using namespace db07;

Destination_receiver::Destination_receiver(Table_definition *description) :
    m_description(description)
{
    horizontal_line();

    for (auto i = m_description->cbegin(); i != m_description->cend(); ++i) {
        cout << '|' << i->name();
    }
    cout << "|\n";

    horizontal_line();
}

Destination_receiver::~Destination_receiver()
{
    horizontal_line();
}

void Destination_receiver::receive(Row &tuple)
{
    
}

void Destination_receiver::horizontal_line() {
    for (auto i = m_description->cbegin(); i != m_description->cend(); ++i) {
        cout << '+';
        for (size_t k = 0; k < i->name().length(); ++k) {
            cout << '-';
        }

    }
    cout << "+\n";
}