#ifndef DB07_INDEX_H
#define DB07_INDEX_H

#include <list>
#include <string>
#include "Attribute.h"


namespace db07 {

    class Btree {

    private:
        struct Node {
            int *keys;
            Node *childNodes;

            Node(int amountOfKeys): keys(new int[amountOfKeys]), childNodes(new Node[amountOfKeys+1]) {};
        };


        struct LeafNode : Node {

            LeafNode(): {};
        };

        Node *root;

    public:
        Btree (Node *root): root(root) {}
    };

}
#endif //DB07_INDEX_H
