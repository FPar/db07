#ifndef TYPE_H
#define TYPE_H

#include <string>

namespace db07 {
    class Type {
    private:

        /*
         * Name of the type.
         */
        const std::string _name;

        /*
         * Length of the type in bytes for fixed length types.
         */
        const int m_length;

    public:
        Type(const std::string name, int length) :
            _name(name),
            m_length(length) { }

        std::string name() const {
            return _name;
        };

        int length() const {
            return m_length;
        };
    };
}

#endif // !TYPE_H
