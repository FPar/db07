#ifndef BITMAP_H
#define BITMAP_H

namespace db07 {
    class Bitmap {
    private:
        unsigned char *m_data;

    public:
        Bitmap(unsigned char *map) : m_data(map)
        {
        }

        bool get(int index) const;
        void set(int index, bool value);
    };
}

#endif // !BITMAP_H
