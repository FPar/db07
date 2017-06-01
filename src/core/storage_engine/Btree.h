#ifndef DB07_INDEX_H
#define DB07_INDEX_H

#include <list>
#include <string>
#include <array>
#include "Column.h"
#include "Row.h"

#define AMOUNTKEYS 4


namespace db07 {

    class Btree {

    private:
        struct Node {
            std::array<int, AMOUNTKEYS> keys = {-1};
            std::array<Node, AMOUNTKEYS+1> childNodes = {nullptr};
            int setKeys = 0;
        };


        struct LeafNode : Node {
            int index = -1;
            Row entries;
        };

        Node *root;

        void insertFullNode(int index, Row entries, Node *node);

        void insertSpaceNode(int index, Row entries, Node *node);

    public:
        void insert(int index, Row entries, Node *node);

        void remove(int index);

        void indexSeek(int index);

        void indexScan(Row *values);


    };

}
#endif //DB07_INDEX_H
