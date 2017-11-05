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
    trie_node *struct_field[10];
    struct_field[1] = new trie_node;
    struct_field[1]->payload = 'a';
    struct_field[1]->is_terminal = true;
    cout << struct_field[1]->payload << endl;
}
