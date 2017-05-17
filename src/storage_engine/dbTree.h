#ifndef DB07_INDEX_H
#define DB07_INDEX_H

#include <list>
#include <string>
#include "Attribute.h"


namespace db07 {

    class dbTree {

    private:
        struct Node {
            int *keys;
            Node *childNodes;
        };

        Node(int amountOfKeys){};

        struct LeafNode : Node {
            std::map<int, Record> entries;
            int size;
        };

        Node *root;

    public:
        dbTree (Node *root): root(root) {}
    };

}
#endif //DB07_INDEX_H
