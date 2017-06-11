
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
    int levelOfNode = node->level;
    int amountOfKeys = node->keys.size();
    if(levelOfNode == 0){ // Leafnode

        LeafNode* splittingAvailable = insertLeafNode(index, entries, node);
        //return splittingAvailable;

    }else{ // Just a Node
        if(amountOfKeys == MAX_AMOUNTKEYS){ // Node full

        }else{ // Node is space

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
LeafNode* db07::Btree::insertLeafNode(int index,  Row *entries, Node *node) {
    LeafNode *newLeafNode = nullptr;
    LeafNode *leafNode = (LeafNode*) node;
    bool foundInsertPosition = false;
    int counter = 0;
    auto i = leafNode->keys.cbegin();
    for(; i < leafNode->keys.cend() && !foundInsertPosition; ++i){
        if((*i)> index){
            foundInsertPosition = true;
            leafNode->keys.insert(i,index);
        }
        ++counter;
    }
    if(!foundInsertPosition){ // empty list for keys or after last element
        leafNode->keys.insert(i,index);
    } else{
        --counter;
    }
    auto j = leafNode->entries.cbegin();
    while(counter > 0) {
        ++j;
        --counter;
    }
    leafNode->entries.insert(j, entries);

    if(leafNode->keys.size() > MAX_AMOUNTKEYS){
        newLeafNode = splitLeafNode(leafNode);
    }
    return newLeafNode;
}


void db07::Btree::splitNode(Node *node) {
   // int middleIndex = findMiddleIndex(node);
}

db07::Btree::LeafNode *db07::Btree::splitLeafNode(db07::Btree::LeafNode *leafNode) {
    int counter = 0;
    LeafNode *newLeaf = new LeafNode();
    auto i = leafNode->keys.cbegin()+MIDDLE_VALUE;
    auto j = leafNode->entries.cbegin() + MIDDLE_VALUE;
    for(; i < leafNode->keys.end() && j < leafNode->entries.cend(); i++, j++){
        newLeaf->keys[counter] = (*i);
        newLeaf->entries[counter] = (*j);
        counter++;
    }
    leafNode->keys.erase(leafNode->keys.cbegin()+ MIDDLE_VALUE, leafNode->keys.cend());
    leafNode->entries.erase(leafNode->entries.cbegin()+ MIDDLE_VALUE, leafNode->entries.cend());
    return newLeaf;
}




