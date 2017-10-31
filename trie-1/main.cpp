//
// Created by Jakub Trmal on 24.10.17.
//
#include <string>
#include <iostream>
#include "trie.hpp"

using namespace std;

void init(trie &trie) {
    trie.root = new trie_node;
}

int main() {

    struct trie trie;
    init(trie);
    delete trie.root;
    cout<<"je to moje"<<endl;
}
