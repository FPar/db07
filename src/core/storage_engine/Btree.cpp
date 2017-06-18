#include "Btree.h"

using namespace std;
using namespace db07;

Btree::Btree() : root(new LeafNode()) {}

void Btree::insert(int index, std::shared_ptr<Row> entries) {
    auto newSearchInfo = search(index, *root);
    if (!(newSearchInfo->found)) {
        unique_ptr<SplitInfo> newSplitInfo = insertNode(index, entries, *root);
        if (newSplitInfo->insertIndex != -1) {
            unique_ptr<Node> newRootNode(new Node());
            newRootNode->level = root->level + 1;
            newRootNode->keys[0] = newSplitInfo->insertIndex;
            newRootNode->childNodes[0] = move(root);
            newRootNode->childNodes[1] = move(newSplitInfo->newNode);
            root = move(newRootNode);
        }
    }
}

std::shared_ptr<Row> Btree::indexSeek(int index) {
    unique_ptr<SearchInfo> newSearchInfo = search(index, *root);
    return newSearchInfo->entry;
}

/**
 * Insert an Entry in the Btree
 * @param Index of the entry
 * @param Entries values of the entry
 * @param node Start node for insertion
 */
unique_ptr<Btree::SplitInfo> Btree::insertNode(int index, std::shared_ptr<Row> entries, Node &node) {
    //Check if node has been initialized
    int levelOfNode = node.level;
    if (levelOfNode == 0) { // Leafnode

        unique_ptr<SplitInfo> splittingAvailable = insertLeafNode(index, entries, node);
        return splittingAvailable;

    } else { // Just a Node
        bool isNodeFound = false;
        int counter = 0;
        unique_ptr<SplitInfo> newSplitInfo(new SplitInfo());
        unique_ptr<SplitInfo> result(new SplitInfo());
        auto j = node.childNodes.cbegin();
        auto i = node.keys.cbegin();
        for (; i < node.keys.cend() && !isNodeFound; ++i, ++j) {
            if (index < (*i)) {
                isNodeFound = true;
                newSplitInfo = insertNode(index, entries, *node.childNodes[counter]);
                if (newSplitInfo->insertIndex != -1) {
                    node.keys.insert(i, newSplitInfo->insertIndex);
                    node.childNodes.insert(j + 1, move(newSplitInfo->newNode));
                    if (node.keys.size() > MAX_AMOUNTKEYS) {
                        result = splitNode(node);
                    }
                }
            }
            counter++;
        }

        if (!isNodeFound) { // Insert at the end
            newSplitInfo = insertNode(index, entries, *node.childNodes[counter]);
            if (newSplitInfo->insertIndex != -1) {
                node.keys.insert(i, newSplitInfo->insertIndex);
                node.childNodes.insert(j + 1, move(newSplitInfo->newNode));
                if (node.keys.size() > MAX_AMOUNTKEYS) {
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
unique_ptr<Btree::SplitInfo> Btree::insertLeafNode(int index, std::shared_ptr<Row> entries, Node &node) {
    unique_ptr<SplitInfo> newSplitInfo(new SplitInfo());
    LeafNode &leafNode = (LeafNode &) node;
    bool foundInsertPosition = false;
    int counter = 0;
    auto i = leafNode.keys.cbegin();
    for (; i < leafNode.keys.cend() && !foundInsertPosition; ++i) {
        if ((*i) > index) {
            foundInsertPosition = true;
            leafNode.keys.insert(i, index);
        }
        ++counter;
    }
    if (!foundInsertPosition) { // empty list for keys or after last element
        leafNode.keys.insert(i, index);
    } else {
        --counter;
    }
    auto j = leafNode.entries.cbegin();
    while (counter > 0) {
        ++j;
        --counter;
    }
    leafNode.entries.insert(j, entries);

    if (leafNode.keys.size() > MAX_AMOUNTKEYS) {
        newSplitInfo = splitLeafNode(leafNode);
    }
    return newSplitInfo;
}

unique_ptr<Btree::SplitInfo> Btree::splitNode(Node &node) {
    int counter = 0;
    int index = node.keys[MIDDLE_VALUE];
    unique_ptr<Node> newNode(new Node());
    newNode->level = node.level;
    unique_ptr<SplitInfo> newSplitInfo(new SplitInfo());
    newSplitInfo->insertIndex = index;
    newSplitInfo->newNode = move(newNode);
    auto i = node.keys.cbegin() + MIDDLE_VALUE + 1;
    auto j = node.childNodes.begin() + MIDDLE_VALUE + 1;
    for (; i < node.keys.end(); i++) {
        newNode->keys[counter] = (*i);
        counter++;
    }
    counter = 0;
    for (; j < node.childNodes.end(); j++) {
        newNode->childNodes[counter] = move(*j);
        counter++;
    }
    node.keys.erase(node.keys.cbegin() + MIDDLE_VALUE, node.keys.cend());
    node.childNodes.erase(node.childNodes.cbegin() + MIDDLE_VALUE + 1, node.childNodes.cend());
    return newSplitInfo;
}

unique_ptr<Btree::SplitInfo> Btree::splitLeafNode(Btree::LeafNode &leafNode) {
    int counter = 0;
    unique_ptr<LeafNode> newLeaf(new LeafNode());
    unique_ptr<SplitInfo> newSplitInfo(new SplitInfo());
    newSplitInfo->insertIndex = leafNode.keys[MIDDLE_VALUE];
    newSplitInfo->newNode = move(newLeaf);
    auto i = leafNode.keys.cbegin() + MIDDLE_VALUE;
    auto j = leafNode.entries.cbegin() + MIDDLE_VALUE;
    for (; i < leafNode.keys.end() && j < leafNode.entries.cend(); i++, j++) {
        newLeaf->keys[counter] = (*i);
        newLeaf->entries[counter] = (*j);
        counter++;
    }
    leafNode.keys.erase(leafNode.keys.cbegin() + MIDDLE_VALUE, leafNode.keys.cend());
    leafNode.entries.erase(leafNode.entries.cbegin() + MIDDLE_VALUE, leafNode.entries.cend());
    return newSplitInfo;
}

unique_ptr<Btree::SearchInfo> Btree::search(int index, Node &node) {
    if (node.level == 0) {
        unique_ptr<SearchInfo> newSearchInfo(new SearchInfo());
        bool isIndexFound = false;
        int counter = 0;
        for (auto i = node.keys.cbegin(); i < node.keys.cend() && !isIndexFound; ++i) {
            if (index == (*i)) {
                LeafNode &leaf = (LeafNode &) node;
                isIndexFound = true;
                newSearchInfo->entry = leaf.entries[counter];
            }
            counter++;
        }
        newSearchInfo->found = isIndexFound;
        return newSearchInfo;
    } else {
        int counter = 0;
        for (auto i = node.keys.cbegin(); i < node.keys.cend(); ++i) {
            if (index < (*i)) {
                return search(index, *node.childNodes[counter]);
            }
            counter++;
        }

        return search(index, *node.childNodes[counter]);
    }
}

void Btree::remove(int index) {

    std:unique_ptr<SearchInfo> newSearchInfo = search(index, *root);
    if(newSearchInfo->found){
        bool result = removeNode(index,*root);
        if(root->level != 0 && result){

        }
    }

}

bool Btree::removeNode(int index, Btree::Node &node) {
    if(node.level == 0){
        LeafNode &leaf = (LeafNode &) node;
        int counter = 0;
        for(auto i = leaf.keys.cbegin(); i < leaf.keys.cend(); ++i){
            if(index == (*i)){
                leaf.keys.erase(i);
                leaf.entries.erase(leaf.entries.cbegin()+counter);
                break;
            }
            counter++;
        }
        return leaf.keys.size() < MIN_CHILDS;

    }else{
        int counter = 0;
        for(auto i = node.keys.cbegin(); i < node.keys.cend(); ++i){
            if(index < (*i)){
                bool result = removeNode(index,*node.childNodes[counter]);
                if(result){
                    Node &sibling = i+1 == node.keys.cend()? *node.childNodes[counter-1]: *node.childNodes[counter+1];
                    if(sibling.keys.size() > MIN_CHILDS){

                    }
                }
            }
            counter++;
        }
    }
    return false;
}


/**
 * Nachbar rechts vorhanden
 * -> size == 2
 *  --> gehe zurück und überprüfe ob linker Nachbar vorhanden ist
 *  ---> linker Nachbar ja
 *  ----> size == 2
 *  ------> merge mit linker oder rechter Nachbar
 *  ----> size < 2
 *  ------> picke letztes key und childnode und füge es beim anderem Childnode an erste stelle bei den keys und chilnodes ein
 *  ---> linker Nachbar nein
 *  ----> merge mit rechter Nachbar
 *
 * -> size < 2
 *  ---> picke erstes key und childnode und füge es beim anderem Childnode an letzter stelle bei den keys und chilnodes ein
 *
 *
 * at the end
 * key anpassung im node wo ich gerade bin
 */










