#ifndef RELATION_H
#define RELATION_H

#include <string>

namespace db07 {
    class Relation {
    private:
        std::string m_name;

    public:
        std::string name() {
            return m_name;
        }
    };
}

#endif // !RELATION_H
