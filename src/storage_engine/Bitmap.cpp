#include "Bitmap.h"

using namespace db07;

bool Bitmap::get(int index) const
{
    int arr_index = index / sizeof(unsigned char);
    int bit_index = 1 << (index % sizeof(unsigned char));
    int value = m_data[arr_index] & bit_index;
    return value;
}

void Bitmap::set(int index, bool value)
{
    int arr_index = index / sizeof(unsigned char);
    int bit_index = 1 << (index % sizeof(unsigned char));
    if (!value)
        m_data[arr_index] |= bit_index;
    else
        m_data[arr_index] &= ~bit_index;
}
