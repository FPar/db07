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
            std::array<Node*, AMOUNTKEYS+1> childNodes = {nullptr};
            Node *prevNode = nullptr;
            int setKeys = 0;
        };


        struct LeafNode : Node {
            std::array<Row*, AMOUNTKEYS> entries = {nullptr};
        };

        Node *root;

        void insertFullNode(int index, Row *entries, Node *node);

        void insertSpaceNode(int index, Row *entries, Node *node);

        void insertLeafNode(int index, Row *entries, LeafNode *leafNode);

        void insertNode(int index, Row *entries, Node *node);

    public:

        void insert(int index, Row *entries);

        void remove(int index);

        LeafNode *indexSeek(int index);

        LeafNode *indexScan(Row *values);


    };

}
#endif //DB07_INDEX_H
