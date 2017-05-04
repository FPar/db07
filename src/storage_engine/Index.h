#ifndef DB07_INDEX_H
#define DB07_INDEX_H

#include <list>
#include <string>

#define KEYSPERNODE 3
#define POINTERSPERNODE 4

class Index {

private:
    struct Node {
        int keys[KEYSPERNODE];
        void *childNodes[POINTERSPERNODE];
    };

    struct Record {
        std::string colName;
        auto colValue;
        Record(std::string cn, auto cv) : colName(cn), colValue(cv) {}
    };

    struct LeafNode {
        std::list<int>  nullEntries;
        std::list<Record> entries;
        LeafNode(std::list<Record> e, std::list<int> ne) : entries(e), nullEntries(ne){}
    };

public:

};


#endif //DB07_INDEX_H
