#ifndef DB07_INDEX_H
#define DB07_INDEX_H

#include <memory>
#include <vector>
#include "Row.h"

namespace db07 {

    class Btree {

    private:

        struct Node {
            std::vector<int> keys;
            std::vector<std::shared_ptr<Node>> childNodes;
            int level = 0;
        };

        struct LeafNode : Node {
            std::vector<std::shared_ptr<Row>> entries;
        };


        struct SplitInfo {
            int insertIndex = -1;
            std::shared_ptr<Node> newNode = nullptr;
        };

        struct SearchInfo {
            bool found = false;
            std::shared_ptr<LeafNode> entry = nullptr;
            int index;
        };

        struct MergeInfo {

        };

        std::shared_ptr<Node> root;

        std::shared_ptr<SplitInfo> insertLeafNode(int index, std::shared_ptr<Row> &entries, Node &leafNode);

        std::shared_ptr<SplitInfo> insertNode(int index, std::shared_ptr<Row> &entries, Node &node);

        std::shared_ptr<SplitInfo> splitNode(Node &node);

        std::shared_ptr<SplitInfo> splitLeafNode(LeafNode &leafNode);

        std::shared_ptr<SearchInfo> search(int index, std::shared_ptr<Node> &node, std::vector<std::pair<int, std::shared_ptr<Node>>>& stack);

        bool removeNode(int index, Node &node);


    public:

        class iterator {
        public:
            iterator();

            iterator(const std::vector<std::pair<int, std::shared_ptr<Node>>> &stack);

            iterator &operator++();

            iterator &operator--();

            std::shared_ptr<Row> operator->();

            std::shared_ptr<Row> operator*();

            friend bool operator==(const iterator &lhs, const iterator &rhs);

            friend bool operator!=(const iterator &lhs, const iterator &rhs);

        private:
            std::vector<std::pair<int, std::shared_ptr<Node>>> stack;
        };

        Btree();

        iterator begin();

        iterator end();

        iterator indexSeek(int index);

        void insert(int index, std::shared_ptr<Row> entries);

        void remove(int index);

        Row *indexScan(Row *values);
    };

}
#endif //DB07_INDEX_H
