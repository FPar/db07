#include "Bitmap.h"

using namespace db07;

bool Bitmap::get(int index) const
{
	int arr_index = index / sizeof(unsigned char);
	int bit_index = 1 << index % sizeof(unsigned char);
	int value = _data[arr_index] & bit_index;
	return value;
}

void Bitmap::set(int index, bool value) const
{
	int arr_index = index / sizeof(unsigned char);
	int bit_index = 1 << index % sizeof(unsigned char);
	if (!value)
		_data[arr_index] |= bit_index;
	else
		_data[arr_index] &= ~bit_index;
}
