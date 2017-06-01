

//void db07::Btree::insert(int index, Row entries, Node *node) {
//    //Check if node has been initialized
//    if(node == nullptr){
//        node = new Node();
//        insert(index, entries, node);
//    }else {
//        //Check if new entry can be inserted in current Node
//        if(node->setKeys == AMOUNTKEYS){
//            insertFullNode(index, entries, node);
//        }else {
//            insertSpaceNode(index, entries, node);
//        }
//    }
//}
//
//void db07::Btree::insertFullNode(int index, Row entries, Node *node) {
//    int counter = 0;
//    for(auto i = node->keys.cbegin(); i < node->keys.cend(); i++){
//        if(index < (*i)){
//            insert(index, entries, &(node->childNodes[counter]));
//        } else {
//            if(i == node->keys.end()){
//                insert(index, entries, &(node->childNodes[counter + 1]));
//            }
//        }
//        counter++;
//    }
//}
//
//
//void db07::Btree::insertSpaceNode(int index, Row entries, Node *node) {
//    for(auto i = node->keys.cbegin(); i < node->keys.cend(); i++){
//
//    }
//}


