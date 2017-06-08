
#include "Btree.h"

db07::Btree::Btree() {
    root = new LeafNode();
}

void db07::Btree::insert(int index, Row *entries) {
    insertNode(index, entries, root);
}

/**
 * Insert an Entry in the Btree
 * @param Index of the entry
 * @param Entries values of the entry
 * @param node Start node for insertion
 */
void db07::Btree::insertNode(int index, Row *entries, Node *node) {
    //Check if node has been initialized
    if(node == nullptr){
        node = new Node();
        insertNode(index, entries, node);
    }else {
        //Check if new entry can be inserted in current Node
        if(node->keys.size() == AMOUNTKEYS){
            insertFullNode(index, entries, node);
        }else {
            insertSpaceNode(index, entries, node);
        }
    }
}

/**
 * Insert an entry in a node that is full
 * @param index Index of the entry
 * @param entries Entries values of the entry
 * @param node Node for insertion
 */
void db07::Btree::insertFullNode(int index, Row *entries, Node *node) {
    int counter = 0;
    for(auto i = node->keys.cbegin(); i < node->keys.cend(); i++){
        if(index < (*i)){
            insertNode(index, entries, node->childNodes[counter]);
            return;
        }
        if(i == node->keys.end()){
                insertNode(index, entries, node->childNodes[counter + 1]);
                return;
        }
        counter++;
    }
}

/**
 * Insert an entry into a node
 * @param index Index of the entry
 * @param entries Entry values of the entry
 * @param node Node for insertion
 */
void db07::Btree::insertSpaceNode(int index, Row *entries, Node *node) {
    int counter = 0;
    for(auto i = node->keys.cbegin(); i < node->keys.cend(); i++){
        if(index < (*i)){
            insertNode(index, entries, node->childNodes[counter]);
            return;
        }
        if((*i) == -1){
            node->keys[counter] = index;
            LeafNode *leaf = new LeafNode();
            leaf->parentNode = node;
            insertLeafNode(index, entries, leaf);
            node->childNodes[counter + 1] =  leaf;
            return;
        }
        if(i == node->keys.end()) {
            insertNode(index, entries, node->childNodes[counter + 1]);
            return;
        }
        counter++;
    }
}

/**
 * Insert an entry into a leafnode
 * @param index Index of the entry
 * @param entries Entry values of the entry
 * @param leafNode LeafNode for insertion
 */
void db07::Btree::insertLeafNode(int index,  Row *entries, LeafNode *leafNode) {
    int counter = 0;
    for(auto i = leafNode->keys.cbegin(); i < leafNode->keys.cend(); i++){
        if((*i) == -1){
            leafNode->keys[counter] = index;
            leafNode->entries[counter] = entries;
            return;
        }
        counter++;
    }
}

int db07::Btree::findMiddleIndex(Node *node) {
    return 0;
}

void db07::Btree::splitNode(Node *node) {
    int middleIndex = findMiddleIndex(node);
}




