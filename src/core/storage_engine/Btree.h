#ifndef DB07_INDEX_H
#define DB07_INDEX_H

#include <list>
#include <string>
#include "Attribute.h"
#include "Tuple.h"

#define AMOUNTKEYS 4


namespace db07 {

    class Btree {

    private:
        struct Node {
            int keys[AMOUNTKEYS];
            Node childNodes[AMOUNTKEYS+1];
        };


        struct LeafNode : Node {

        };

        Node *root;

    public:
        void insert(int index, std::vector<Tuple> entries);

        void remove(int index);

        void indexSeek(int index);

        void indexScan(Tuple *values);


    };

}
#endif //DB07_INDEX_H
