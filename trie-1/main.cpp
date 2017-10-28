//
// Created by Jakub Trmal on 24.10.17.
//
#include <string>
#include <iostream>
#include "trie.hpp"

using namespace std;

int main() {

    trie_node *node = new trie_node;
    cout << "alok: " << node << endl;
    cout << node->is_terminal << endl;


    delete node;

    cout << "dealok: " << node << endl;
    cout << node->is_terminal << endl;

    
    string str = "word";
    cout << str[0] << endl;
    cout << str[2] << endl;
}
