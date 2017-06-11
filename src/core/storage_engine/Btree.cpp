
#include "Btree.h"

db07::Btree::Btree() {
    root = new LeafNode();
}

void db07::Btree::insert(int index, Row *entries) {
    // TODO vorher search
    SplitInfo *newSplitInfo = insertNode(index, entries, root);
    if(newSplitInfo->insertIndex != -1){
        Node *newRootNode = new Node();
        newRootNode->level = root->level+1;
        newRootNode->keys[0] = newSplitInfo->insertIndex;
        newRootNode->childNodes[0] = root;
        newRootNode->childNodes[1] = newSplitInfo->newNode;
        root = newRootNode;
    }
}

/**
 * Insert an Entry in the Btree
 * @param Index of the entry
 * @param Entries values of the entry
 * @param node Start node for insertion
 */
db07::Btree::SplitInfo* db07::Btree::insertNode(int index, Row *entries, Node *node) {
    //Check if node has been initialized
    int levelOfNode = node->level;
    int amountOfKeys = node->keys.size();
    if(levelOfNode == 0){ // Leafnode

        SplitInfo* splittingAvailable = insertLeafNode(index, entries, node);
        return splittingAvailable;

    }else{ // Just a Node
        bool isNodeFound = false;
        int counter = 0;
        SplitInfo *newSplitInfo = new SplitInfo();
        SplitInfo *result = new SplitInfo();
        auto j = node->childNodes.cbegin();
        auto i = node->keys.cbegin();
        for(; i < node->keys.cend() && !isNodeFound ; ++i,++j){
            if(index < (*i)){
                isNodeFound = true;
                newSplitInfo = insertNode(index,entries,node->childNodes[counter]);
                if(newSplitInfo->insertIndex != -1){
                    node->keys.insert(i,newSplitInfo->insertIndex);
                    node->childNodes.insert(j+1,newSplitInfo->newNode);
                    if(node->keys.size() > MAX_AMOUNTKEYS){
                        result = splitNode(node);
                    }
                }
            }
            counter++;
        }

        if(!isNodeFound){ // Insert at the end
            newSplitInfo = insertNode(index,entries,node->childNodes[counter]);
            if(newSplitInfo->insertIndex != -1){
                node->keys.insert(i,newSplitInfo->insertIndex);
                node->childNodes.insert(j+1,newSplitInfo->newNode);
                if(node->keys.size() > MAX_AMOUNTKEYS){
                    result = splitNode(node);
                }
            }
        }

        return result;


    }
}

/**
 * Insert an entry into a leafnode
 * @param index Index of the entry
 * @param entries Entry values of the entry
 * @param leafNode LeafNode for insertion
 */
db07::Btree::SplitInfo *db07::Btree::insertLeafNode(int index, Row *entries, Node *node) {
    SplitInfo *newSplitInfo = new SplitInfo();
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
        newSplitInfo = splitLeafNode(leafNode);
    }
    return newSplitInfo;
}


db07::Btree::SplitInfo *db07::Btree::splitNode(Node *node) {
    int counter = 0;
    int index = node->keys[MIDDLE_VALUE];
    Node *newNode = new Node();
    newNode->level = node->level;
    SplitInfo *newSplitInfo = new SplitInfo();
    newSplitInfo->insertIndex = index;
    newSplitInfo->newNode = newNode;
    auto i = node->keys.cbegin()+MIDDLE_VALUE + 1;
    auto j = node->childNodes.cbegin() + MIDDLE_VALUE + 1;
    for(; i < node->keys.end(); i++){
        newNode->keys[counter] = (*i);
        counter++;
    }
    counter = 0;
    for(;j < node->childNodes.cend(); j++){
        newNode->childNodes[counter] = (*j);
        counter++;
    }
    node->keys.erase(node->keys.cbegin()+ MIDDLE_VALUE, node->keys.cend());
    node->childNodes.erase(node->childNodes.cbegin()+ MIDDLE_VALUE + 1, node->childNodes.cend());
    return newSplitInfo;
}

db07::Btree::SplitInfo *db07::Btree::splitLeafNode(db07::Btree::LeafNode *leafNode) {
    int counter = 0;
    LeafNode *newLeaf = new LeafNode();
    SplitInfo *newSplitInfo = new SplitInfo();
    newSplitInfo->insertIndex = leafNode->keys[MIDDLE_VALUE];
    newSplitInfo->newNode = newLeaf;
    auto i = leafNode->keys.cbegin()+MIDDLE_VALUE;
    auto j = leafNode->entries.cbegin() + MIDDLE_VALUE;
    for(; i < leafNode->keys.end() && j < leafNode->entries.cend(); i++, j++){
        newLeaf->keys[counter] = (*i);
        newLeaf->entries[counter] = (*j);
        counter++;
    }
    leafNode->keys.erase(leafNode->keys.cbegin()+ MIDDLE_VALUE, leafNode->keys.cend());
    leafNode->entries.erase(leafNode->entries.cbegin()+ MIDDLE_VALUE, leafNode->entries.cend());
    return newSplitInfo;
}




