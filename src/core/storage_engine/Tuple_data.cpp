#include "Tuple_data.h"

using namespace std;
using namespace db07;

Tuple_data::Tuple_data(vector<Tuple_value> &values)
{
    // Get size
    int size = 0;
    for (auto i = values.cbegin(); i != values.cend(); ++i) {
        size += i->length();
    }

    // Write data
    m_data = new unsigned char[size];
    int index;
    for (auto i = values.cbegin(); i != values.cend(); ++i) {
        
    }
}

Tuple_data::~Tuple_data()
{
    delete[] m_data;
}

void Tuple_data::get_indexes(const Table_definition &description, int *indexes)
{
    int arr_i = 0;
    int position = 0;
    for (auto i = description.cbegin(); i != description.cend(); ++i) {
        indexes[arr_i] = position;
        Type *type = i->type();
        position += type->length();
    }
}

void Tuple_data::set_value(int position, Tuple_value &value)
{
}
