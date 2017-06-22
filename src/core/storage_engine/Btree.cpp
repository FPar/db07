#include "Btree.h"

#define MAX_AMOUNTKEYS 4
#define MIDDLE_VALUE 2
#define MIN_CHILDS MAX_AMOUNTKEYS/MIDDLE_VALUE

using namespace std;
using namespace db07;

Btree::Btree() : root(new LeafNode()) {}

void Btree::insert(int index, std::shared_ptr<Row> entries) {
    vector<pair<int, shared_ptr<Node>>> stack;
    auto newSearchInfo = search(index, root, stack);
    if (!(newSearchInfo->found)) {
        shared_ptr<SplitInfo> newSplitInfo = insertNode(index, entries, *root);
        if (newSplitInfo->insertIndex != -1) {
            shared_ptr<Node> newRootNode(new Node());
            newRootNode->level = root->level + 1;
            newRootNode->keys.push_back(newSplitInfo->insertIndex);
            newRootNode->childNodes.push_back(root);
            newRootNode->childNodes.push_back(newSplitInfo->newNode);
            root = newRootNode;
        }
    }
}

Btree::iterator Btree::begin() {
    vector<pair<int, shared_ptr<Node>>> stack;
    shared_ptr<Node> ptr = root;
    while (ptr->level > 0) {
        stack.push_back(make_pair(0, ptr));
        ptr = ptr->childNodes[0];
    }
    stack.push_back(make_pair(0, ptr));
    return Btree::iterator(stack);
}

Btree::iterator Btree::end() {
    return Btree::iterator();
}

Btree::iterator Btree::indexSeek(int index) {
    vector<pair<int, shared_ptr<Node>>> stack;
    shared_ptr<SearchInfo> newSearchInfo = search(index, root, stack);
    return Btree::iterator(stack);
}

/**
 * Insert an Entry in the Btree
 * @param Index of the entry
 * @param Entries values of the entry
 * @param node Start node for insertion
 */
shared_ptr<Btree::SplitInfo> Btree::insertNode(int index, std::shared_ptr<Row> &entries, Node &node) {
    //Check if node has been initialized
    int levelOfNode = node.level;
    if (levelOfNode == 0) { // Leafnode

        shared_ptr<SplitInfo> splittingAvailable = insertLeafNode(index, entries, node);
        return splittingAvailable;

    } else { // Just a Node
        bool isNodeFound = false;
        int counter = 0;
        shared_ptr<SplitInfo> newSplitInfo(new SplitInfo());
        shared_ptr<SplitInfo> result(new SplitInfo());
        auto j = node.childNodes.cbegin();
        auto i = node.keys.cbegin();
        for (; i < node.keys.cend() && !isNodeFound; ++i, ++j) {
            if (index < (*i)) {
                isNodeFound = true;
                newSplitInfo = insertNode(index, entries, *node.childNodes[counter]);
                if (newSplitInfo->insertIndex != -1) {
                    node.keys.insert(i, newSplitInfo->insertIndex);
                    node.childNodes.insert(j + 1, newSplitInfo->newNode);
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
                node.childNodes.insert(j + 1, newSplitInfo->newNode);
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
shared_ptr<Btree::SplitInfo> Btree::insertLeafNode(int index, std::shared_ptr<Row> &entries, Node &node) {
    shared_ptr<SplitInfo> newSplitInfo(new SplitInfo());
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

shared_ptr<Btree::SplitInfo> Btree::splitNode(Node &node) {
    int counter = 0;
    int index = node.keys[MIDDLE_VALUE];
    Node *newNode(new Node());
    newNode->level = node.level;
    shared_ptr<SplitInfo> newSplitInfo(new SplitInfo());
    newSplitInfo->insertIndex = index;
    newSplitInfo->newNode = shared_ptr<Node>(newNode);
    auto i = node.keys.cbegin() + MIDDLE_VALUE + 1;
    auto j = node.childNodes.begin() + MIDDLE_VALUE + 1;
    for (; i < node.keys.end(); i++) {
        newNode->keys.push_back(*i);
        counter++;
    }
    counter = 0;
    for (; j < node.childNodes.end(); j++) {
        newNode->childNodes.push_back(*j);
        counter++;
    }
    node.keys.erase(node.keys.cbegin() + MIDDLE_VALUE, node.keys.cend());
    node.childNodes.erase(node.childNodes.cbegin() + MIDDLE_VALUE + 1, node.childNodes.cend());
    return newSplitInfo;
}

shared_ptr<Btree::SplitInfo> Btree::splitLeafNode(Btree::LeafNode &leafNode) {
    int counter = 0;
    LeafNode *newLeaf = new LeafNode();
    shared_ptr<SplitInfo> newSplitInfo(new SplitInfo());
    newSplitInfo->insertIndex = leafNode.keys[MIDDLE_VALUE];
    newSplitInfo->newNode = shared_ptr<LeafNode>(newLeaf);
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

shared_ptr<Btree::SearchInfo>
Btree::search(int index, shared_ptr<Node> &node, vector<pair<int, shared_ptr<Node>>> &stack) {
    if (node->level == 0) {
        shared_ptr<SearchInfo> newSearchInfo(new SearchInfo());
        bool isIndexFound = false;
        int counter = 0;
        for (auto i = node->keys.cbegin(); i < node->keys.cend() && !isIndexFound; ++i) {
            if (index == (*i)) {
                auto leaf = static_pointer_cast<LeafNode>(node);
                isIndexFound = true;
                newSearchInfo->entry = leaf;
                newSearchInfo->index = counter;

                stack.push_back(make_pair(counter, leaf));

                break;
            }
            counter++;
        }
        newSearchInfo->found = isIndexFound;
        return newSearchInfo;
    } else {
        int counter = 0;
        for (auto i = node->keys.cbegin(); i < node->keys.cend(); ++i) {
            if (index < (*i)) {
                stack.push_back(make_pair(counter, node));
                return search(index, node->childNodes[counter], stack);
            }
            counter++;
        }

        return search(index, node->childNodes[counter], stack);
    }
}

void Btree::remove(int index) {
    vector<pair<int, shared_ptr<Node>>> stack;
    shared_ptr<SearchInfo> newSearchInfo = search(index, root, stack);
    if (newSearchInfo->found) {
        bool result = removeNode(index, *root);
        if (root->level != 0 && result) {

        }
    }

}

bool Btree::borrowLeaf(Btree::LeafNode &leafNode, Btree::Node &parent, std::vector<int>::const_iterator &it_parent,
                       int curr_pos) {
    if (it_parent + 1 != parent.keys.cend()) {
        LeafNode &rightSibling = (LeafNode &) parent.childNodes[curr_pos + 1];
        if (rightSibling.keys.size() > MIN_CHILDS) {
            //Borrow LeafNode entry from rightSibling
            leafNode.keys.push_back(rightSibling.keys[0]);
            leafNode.entries.push_back(rightSibling.entries[0]);

            //Remove borrowed entry from rightSibling
            rightSibling.keys.erase(rightSibling.keys.cbegin());
            rightSibling.entries.erase(rightSibling.entries.cbegin());

            //Update parent Node index key
            parent.keys[curr_pos] = rightSibling.keys[0];

            return leafNode.keys.size() < MIN_CHILDS;
        }
    }

    //Check for left Sibling
    if (it_parent != parent.keys.cbegin()) {
        LeafNode &leftSibling = (LeafNode &) parent.childNodes[curr_pos - 1];
        if (leftSibling.keys.size() > MIN_CHILDS) {
            //Borrow LeafNode entry from leftSibling
            leafNode.keys.insert(leafNode.keys.cbegin(),
                                 leftSibling.keys[leftSibling.keys.size() - 1]);
            leafNode.entries.insert(leafNode.entries.cbegin(),
                                    leftSibling.entries[leftSibling.entries.size() - 1]);

            //Remove borrowed entry from leftSibling
            leftSibling.keys.erase(leftSibling.keys.cend() - 1);
            leftSibling.entries.erase(leftSibling.entries.cend() - 1);

            //Update parent Node index key
            parent.keys[curr_pos] = leafNode.keys[0];

            return leafNode.keys.size() < MIN_CHILDS;
        }
    }

    return false;
}

bool Btree::borrowNode(Btree::Node &innerNode, Btree::Node &parent, std::vector<int>::const_iterator &it_parent,
                       int curr_pos) {

    if (it_parent + 1 != parent.keys.cend()) {
        Node &rightSibling = *parent.childNodes[curr_pos + 1];
        if (rightSibling.keys.size() > MIN_CHILDS) {
            //Borrow LeafNode entry from rightSibling
            innerNode.keys.push_back(rightSibling.keys[0]);
            innerNode.childNodes.push_back(rightSibling.childNodes[0]);

            //Remove borrowed entry from rightSibling
            rightSibling.keys.erase(rightSibling.keys.cbegin());
            rightSibling.childNodes.erase((rightSibling.childNodes.cbegin()));

            //Update parent Node index key
            parent.keys[curr_pos] = rightSibling.keys[0];

            return innerNode.keys.size() < MIN_CHILDS;
        }
    }

    if (it_parent != parent.keys.cbegin()) {
        Node &leftSibling = *parent.childNodes[curr_pos + 1];
        if (leftSibling.keys.size() > MIN_CHILDS) {
            //Borrow LeafNode entry from leftSibling
            innerNode.keys.insert(innerNode.keys.cbegin(),
                                  leftSibling.keys[leftSibling.keys.size() - 1]);
            innerNode.childNodes.insert(innerNode.childNodes.cbegin(),
                                        leftSibling.childNodes[leftSibling.childNodes.size() -
                                                               1]);

            //Remove borrowed entry from leftSibling
            leftSibling.keys.erase(leftSibling.keys.cend() - 1);
            leftSibling.childNodes.erase(leftSibling.childNodes.cend() - 1);

            //Update parent Node index key
            parent.keys[curr_pos] = innerNode.keys[0];

            return innerNode.keys.size() < MIN_CHILDS;
        }
    }

    return false;
}


bool Btree::mergeLeaf(Btree::LeafNode &leafNode, Btree::Node &parent, std::vector<int>::const_iterator &it_parent,
                      int curr_pos) {
    if(it_parent != parent.keys.cbegin()){
        LeafNode &leftSibling = (LeafNode &) parent.childNodes[curr_pos - 1];

        //Insert leafNode values into left sibling
        leftSibling.keys.push_back(leafNode.keys[0]);
        leftSibling.entries.push_back(leafNode.entries[0]);

        //Delete the leaf node that has been merged
        parent.keys.erase(it_parent -1);
        parent.childNodes.erase(parent.childNodes.cbegin() + curr_pos);

        return true;
    }

    if(it_parent + 1 != parent.keys.cend()){

    }


    return false;
}

bool Btree::removeNode(int index, Btree::Node &node) {
    int counter = 0;
    if (node.level == 0) {
        LeafNode &leaf = (LeafNode &) node;
        counter = 0;
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
        counter = 0;
        for (auto i = node.keys.cbegin(); i < node.keys.cend(); ++i) {
            if (index < (*i)) {
                Node &rmNode = *node.childNodes[counter];
                bool result = removeNode(index, rmNode);
                if (result) {
                    //Borrow Mechanism
                    //Check if underlying Node is a LeafNode
                    if (rmNode.level == 0) {
                        LeafNode &rmLeafNode = (LeafNode &) node.childNodes[counter];
                        bool res = borrowLeaf(rmLeafNode, node, i, counter);

                        if(res){
                            return res;
                        }

                        return mergeLeaf(rmLeafNode, node, i, counter);

                        //Merge Mechanism
                    } else { //If underlying node is an internal Node
                        //Borrow Mechanism
                        return borrowNode(rmNode, node, i, counter);
                    }

                    //Merge Mechanism
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

Btree::iterator::iterator() {
}

Btree::iterator::iterator(const vector<pair<int, shared_ptr<Node>>> &stack) : stack(stack) {
}

Btree::iterator &Btree::iterator::operator++() {
    pair<int, shared_ptr<Node>> top = stack.back();
    stack.pop_back();

    unsigned int cur_index = top.first + 1;

    {
        shared_ptr<LeafNode> leaf = static_pointer_cast<LeafNode>(top.second);

        if (cur_index < leaf->entries.size()) {
            stack.push_back(make_pair(cur_index, leaf));
            return *this;
        }
    }

    shared_ptr<Node> ptr = top.second;

    while (!stack.empty()) {
        top = stack.back();
        stack.pop_back();

        cur_index = top.first + 1;
        ptr = top.second;

        if (cur_index < ptr->childNodes.size()) {
            stack.push_back(make_pair(cur_index, ptr));
            break;
        }
    }

    if (cur_index >= ptr->childNodes.size()) {
        return *this;
    }

    ptr = ptr->childNodes[cur_index];
    while (ptr->level > 0) {
        stack.push_back(make_pair(0, ptr));
        ptr = ptr->childNodes[0];
    }
    stack.push_back(make_pair(0, ptr));

    return *this;
}

Btree::iterator &Btree::iterator::operator--() {
    return *this;
}

shared_ptr<Row> Btree::iterator::operator->() {
    return static_pointer_cast<LeafNode>(stack.back().second)->entries[stack.back().first];
}

shared_ptr<Row> Btree::iterator::operator*() {
    return static_pointer_cast<LeafNode>(stack.back().second)->entries[stack.back().first];
}

namespace db07 {
    bool operator==(const Btree::iterator &lhs, const Btree::iterator &rhs) {
        return lhs.stack.size() == rhs.stack.size() && (lhs.stack.empty() || lhs.stack.back() == rhs.stack.back());
    }

    bool operator!=(const Btree::iterator &lhs, const Btree::iterator &rhs) {
        return !(lhs == rhs);
    }


}