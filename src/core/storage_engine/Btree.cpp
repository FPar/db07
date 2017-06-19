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
            newRootNode->keys.push_back(newSplitInfo->insertIndex);
            newRootNode->childNodes.push_back(move(root));
            newRootNode->childNodes.push_back(move(newSplitInfo->newNode));
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
    Node* newNode(new Node());
    newNode->level = node.level;
    unique_ptr<SplitInfo> newSplitInfo(new SplitInfo());
    newSplitInfo->insertIndex = index;
    newSplitInfo->newNode = unique_ptr<Node>(newNode);
    auto i = node.keys.cbegin() + MIDDLE_VALUE + 1;
    auto j = node.childNodes.begin() + MIDDLE_VALUE + 1;
    for (; i < node.keys.end(); i++) {
        newNode->keys.push_back(*i);
        counter++;
    }
    counter = 0;
    for (; j < node.childNodes.end(); j++) {
        newNode->childNodes.push_back(move(*j));
        counter++;
    }
    node.keys.erase(node.keys.cbegin() + MIDDLE_VALUE, node.keys.cend());
    node.childNodes.erase(node.childNodes.cbegin() + MIDDLE_VALUE + 1, node.childNodes.cend());
    return newSplitInfo;
}

unique_ptr<Btree::SplitInfo> Btree::splitLeafNode(Btree::LeafNode &leafNode) {
    int counter = 0;
    LeafNode* newLeaf = new LeafNode();
    unique_ptr<SplitInfo> newSplitInfo(new SplitInfo());
    newSplitInfo->insertIndex = leafNode.keys[MIDDLE_VALUE];
    newSplitInfo->newNode = unique_ptr<LeafNode>(newLeaf);
    auto i = leafNode.keys.cbegin() + MIDDLE_VALUE;
    auto j = leafNode.entries.cbegin() + MIDDLE_VALUE;
    for (; i < leafNode.keys.end() && j < leafNode.entries.cend(); i++, j++) {
        newLeaf->keys.push_back(*i);
        newLeaf->entries.push_back(*j);
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
                LeafNode &leaf = static_cast<LeafNode &>(node);
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

    unique_ptr<SearchInfo> newSearchInfo = search(index, *root);
    if (newSearchInfo->found) {
        bool result = removeNode(index, *root);
        if (root->level != 0 && result) {

        }
    }

}

bool Btree::removeNode(int index, Btree::Node &node) {
    if (node.level == 0) {
        LeafNode &leaf = (LeafNode &) node;
        int counter = 0;
        for (auto i = leaf.keys.cbegin(); i < leaf.keys.cend(); ++i) {
            if (index == (*i)) {
                leaf.keys.erase(i);
                leaf.entries.erase(leaf.entries.cbegin() + counter);
                break;
            }
            counter++;
        }
        return leaf.keys.size() < MIN_CHILDS;

    } else {
        int counter = 0;
        for (auto i = node.keys.cbegin(); i < node.keys.cend(); ++i) {
            if (index < (*i)) {
                Node &rmNode = *node.childNodes[counter];
                bool result = removeNode(index, rmNode);
                if (result) {
                    //Borrow Mechanism
                    //Check if underlying Node is a LeafNode
                    if (rmNode.level == 0) {
                        LeafNode &rmLeafNode = (LeafNode &) node.childNodes[counter];
                        if (i + 1 != node.keys.cend()) {
                            //Check for right rightSibling
                            LeafNode &rightSibling = (LeafNode &) node.childNodes[counter + 1];
                            if (rightSibling.keys.size() > MIN_CHILDS) {
                                //Borrow LeafNode entry from rightSibling
                                rmLeafNode.keys.push_back(rightSibling.keys[0]);
                                rmLeafNode.entries.push_back(rightSibling.entries[0]);

                                //Remove borrowed entry from rightSibling
                                rightSibling.keys.erase(rightSibling.keys.cbegin());
                                rightSibling.entries.erase(rightSibling.entries.cbegin());

                                //Update parent Node index key
                                node.keys[counter] = rightSibling.keys[0];

                                return rmLeafNode.keys.size() < MIN_CHILDS;
                            }
                        }

                        //Check for left Sibling
                        if (i != node.keys.cbegin()) {
                            LeafNode &leftSibling = (LeafNode &) node.childNodes[counter - 1];
                            if (leftSibling.keys.size() > MIN_CHILDS) {
                                //Borrow LeafNode entry from leftSibling
                                rmLeafNode.keys.insert(rmLeafNode.keys.cbegin(),
                                                       leftSibling.keys[leftSibling.keys.size() - 1]);
                                rmLeafNode.entries.insert(rmLeafNode.entries.cbegin(),
                                                          leftSibling.entries[leftSibling.entries.size() - 1]);

                                //Remove borrowed entry from leftSibling
                                leftSibling.keys.erase(leftSibling.keys.cend() - 1);
                                leftSibling.entries.erase(leftSibling.entries.cend() - 1);

                                //Update parent Node index key
                                node.keys[counter] = rmLeafNode.keys[0];

                                return rmLeafNode.keys.size() < MIN_CHILDS;
                            }
                        }

                        //Merge Mechanism
                    } else { //If underlying node is an internal Node
                        //Borrow Mechanism
                        if (i + 1 != node.keys.cbegin()) {
                            Node &rightSibling = *node.childNodes[counter + 1];
                            if (rightSibling.keys.size() > MIN_CHILDS) {
                                //Borrow LeafNode entry from rightSibling
                                rmNode.keys.push_back(rightSibling.keys[0]);
                                rmNode.childNodes.push_back(move(rightSibling.childNodes[0]));

                                //Remove borrowed entry from rightSibling
                                rightSibling.keys.erase(rightSibling.keys.cbegin());
                                rightSibling.childNodes.erase((rightSibling.childNodes.cbegin()));

                                //Update parent Node index key
                                node.keys[counter] = rightSibling.keys[0];

                                return rmNode.keys.size() < MIN_CHILDS;
                            }
                        }

                        if (i != node.keys.cbegin()) {
                            Node &leftSibling = *node.childNodes[counter + 1];
                            if (leftSibling.keys.size() > MIN_CHILDS) {
                                //Borrow LeafNode entry from leftSibling
                                rmNode.keys.insert(rmNode.keys.cbegin(),
                                                   leftSibling.keys[leftSibling.keys.size() - 1]);
                                rmNode.childNodes.insert(rmNode.childNodes.cbegin(),
                                                         move(leftSibling.childNodes[leftSibling.childNodes.size() -
                                                                                     1]));

                                //Remove borrowed entry from leftSibling
                                leftSibling.keys.erase(leftSibling.keys.cend() - 1);
                                leftSibling.childNodes.erase(leftSibling.childNodes.cend() - 1);

                                //Update parent Node index key
                                node.keys[counter] = rmNode.keys[0];

                                return rmNode.keys.size() < MIN_CHILDS;
                            }
                        }

                        //Merge Mechanism
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










