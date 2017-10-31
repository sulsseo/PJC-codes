#include "trie.hpp"

bool insert(trie_node *node, std::string str) {
    if (str.size() == 0) {
        if (!node->is_terminal) {
            node->is_terminal = true;
            return true;
        } else return false;
    }
    char inspect = str.at(0);

    int i = 0;
    while (i <= num_chars) {
        if (node->children[i] == nullptr) {
            node->children[i] = new trie_node;
            node->children[i]->payload = inspect;
            node->children[i]->parent = node;
            return insert(node->children[i], str.substr(1, str.size()));
        } else if (node->children[i]->payload == inspect)
            return insert(node->children[i], str.substr(1, str.size()));
        ++i;
    }
    return false;
}

bool insert(trie &trie, const std::string &str) {
    char inspect = 0;

    if (str.size() != 0) inspect = str.at(0);

    trie_node *node = trie.root;

    int i = 0;
    while (i <= num_chars) {
        if (node->children[i] == nullptr) {
            // no matching children
            node->children[i] = new trie_node;
            node->children[i]->payload = inspect;
            node->children[i]->parent = node;
            if (inspect == 0) {
                trie.size++;
                return true;
            }
            if (insert(node->children[i], str.substr(1, str.size()))) {
                trie.size++;
                return true;
            } else return false;
        } else if (node->children[i]->payload == inspect) {
            if (insert(node->children[i], str.substr(1, str.size()))) {
                trie.size++;
                return true;
            } else return false;
        }
        ++i;
    }
    return false;
}

bool contains(trie_node *node, std::string str) {
    if (str.size() == 0) {
        return node->is_terminal;
    }

    char inspect = str.at(0);
    for (int i = 0; i < num_chars; ++i) {
        if (node->children[i] == nullptr) return false;
        if (node->children[i]->payload == inspect) {
            return contains(node->children[i], str.substr(1, str.size()));
        }
    }
    return false;
}

bool contains(const trie &trie, const std::string &str) {
    char inspect = 0;
    if (trie.size == 0) return false;
    if (str.size() != 0) inspect = str.at(0);

    trie_node *node = trie.root;

    for (int i = 0; i < num_chars; ++i) {
        if (node->children[i] == nullptr) return false;
        if (node->children[i]->payload == inspect) {
            if (inspect == 0) return true;
            return contains(node->children[i], str.substr(1, str.size()));
        }
    }
    return false;
}

void insert_all(trie &trie, const std::vector<std::string> &items) {
    for (int i = 0; i < items.size(); ++i) {
        insert(trie, items.at(i));
    }
}

void init(trie &trie) {
    trie.root = new trie_node;
}

/*
bool erase(trie_node *node, std::string str) {
    if (str.size() == 0) {
        // end of string
        if (node->is_terminal) {
            if (node->children[0] == nullptr) {
                delete node;
//                node = nullptr; // nulovani
                return true;
            } else {
                node->is_terminal = false;
                return true;
            }
        } else {
            return false;
        }
    }

    char inspect = str.at(0);

    int i = 0;
    while (i <= num_chars) {
        if (node->children[i] == nullptr) return false;

        else if (node->children[i]->payload == inspect) {
            return erase(node->children[i], str.substr(1, str.size()));
        }
    }
    return false;
}

bool erase(trie &trie, const std::string &str) {
    char inspect = 0;
    if (str.size() != 0) inspect = str.at(0);

    trie_node *node = trie.root;

    int i = 0;
    while (i <= num_chars) {
        if (node->children[i] == nullptr) {
            // no char to erase
            return false;
        } else if (node->children[i]->payload == inspect) {
            if (erase(node->children[i], str.substr(1, str.size()))) {
                trie.size--;
                return true;
            } else return false;
        }
        ++i;
    }
    return false;
}
*/

/*
 * get index of equal char
 */
bool erase(trie_node *node, const std::string &str, int index) {
    if (index+1 == str.size()) {
        // in important node
        if (node->is_terminal) {
            node->is_terminal = false;
            if (node->children[0] == nullptr) {
                delete node; // not deleting children full of nulls
//                node= nullptr;
                return true;
            } else return true;
        } else return false;
    }

    int i = 0;
    while (i <= num_chars) {
        if (node->children[i] == nullptr) {
            return false;
        } else if (node->children[i]->payload == str[index + 1]) {
            if (erase(node->children[i], str, index + 1)) {
                // succ deleting clean this node and return true
                if (node->is_terminal) {
                    return true;
                } else {
                    if (node->children[0] == nullptr) {
                        delete node;
//                        node= nullptr;
                        return true;
                    } else return true;
                }
            } else return false;
        }
        ++i;
    }
}

bool erase(trie &trie, const std::string &str) {
    int i = 0;
    while (i <= num_chars) {
        if (trie.root->children[i] == nullptr) {
            return false;
        } else if (trie.root->children[i]->payload == str[0]) {
            // got child
            if (erase(trie.root->children[i], str, 0)) {
                trie.size--;
                return true;
            } else return false;
        }
        ++i;
    }
    return false;
}

void deallocate(trie_node *node) {
    for (trie_node *&child : node->children) {
        if (child != nullptr) {
            deallocate(child);
        } else break;
    }
    delete node;
}

void deallocate(trie &trie) {
    for (trie_node *&child : trie.root->children) {
        if (child != nullptr) {
            deallocate(child);
        } else break;
    }
    delete trie.root;
}

size_t size(const trie &trie) {
    return trie.size;
}

bool empty(const trie &trie) {
    return trie.size == 0;
}
