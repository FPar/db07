#ifndef DB07_INDEX_H
#define DB07_INDEX_H

#include <list>
#include <string>
#include <array>
#include "Column.h"
#include "Row.h"

#define MAX_AMOUNTKEYS 4
#define MIDDLE_VALUE 2
#define MIN_CHILDS MAX_AMOUNTKEYS/MIDDLE_VALUE


namespace db07 {

    class Btree {

    private:

        struct Node {
            std::vector<int> keys;
            std::vector<std::unique_ptr<Node>> childNodes;
            std::unique_ptr<Node> parentNode = nullptr;
            int level = 0;
        };

        struct LeafNode : Node {
            std::vector<std::shared_ptr<Row>> entries;
        };


        struct SplitInfo {
            int insertIndex = -1;
            std::unique_ptr<Node> newNode = nullptr;
        };

        struct SearchInfo {
            bool found = false;
            std::shared_ptr<Row> entry = nullptr;
        };

        struct MergeInfo {

        };

        std::unique_ptr<Node> root;

        std::unique_ptr<SplitInfo> insertLeafNode(int index, std::shared_ptr<Row> entries, Node &leafNode);

        std::unique_ptr<SplitInfo> insertNode(int index, std::shared_ptr<Row> entries, Node &node);

        std::unique_ptr<SplitInfo> splitNode(Node &node);

        std::unique_ptr<SplitInfo> splitLeafNode(LeafNode &leafNode);

        std::unique_ptr<SearchInfo> search(int index, Node &node);

        bool removeNode(int index, Node &node);



    public:

        Btree();

        void insert(int index, std::shared_ptr<Row> entries);

        void remove(int index);

        std::shared_ptr<Row> indexSeek(int index);

        Row *indexScan(Row *values);


    };

}
#endif //DB07_INDEX_H
