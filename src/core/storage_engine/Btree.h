#ifndef DB07_INDEX_H
#define DB07_INDEX_H

#include <list>
#include <string>
#include <array>
#include "Column.h"
#include "Row.h"

#define MAX_AMOUNTKEYS 4
#define MIDDLE_VALUE 2


namespace db07 {

    class Btree {

    private:

        struct Node {
            std::vector<int> keys;
            std::vector<Node*> childNodes;
            Node *parentNode = nullptr;
            int level = 0;
        };

        struct SplitInfo {
            int insertIndex = -1;
            Node * newNode = nullptr;
        };


        struct LeafNode : Node {
            std::vector<Row*> entries;
        };

        Node *root;


        SplitInfo * insertLeafNode(int index, Row *entries, Node *leafNode);

        SplitInfo* insertNode(int index, Row *entries, Node *node);

        SplitInfo* splitNode(Node *node);

        SplitInfo* splitLeafNode(LeafNode *leafNode);

    public:

		Btree();

        void insert(int index, Row *entries);

        void remove(int index);

        LeafNode *indexSeek(int index);

        LeafNode *indexScan(Row *values);


    };

}
#endif //DB07_INDEX_H
