#ifndef BITMAP_H
#define BITMAP_H

namespace db07
{
	class Bitmap
	{
	public:
		Bitmap(unsigned char* map) : _data(map)
		{
		}

		bool get(int index) const;
		void set(int index, bool value) const;

	private:
		unsigned char* _data;
	};
}

#endif // !BITMAP_H
