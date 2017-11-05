#include "trie.hpp"

bool insert(trie_node *node, std::string str) {
    if (str.empty()) {
        if (!node->is_terminal) {
            node->is_terminal = true;
            return true;
        } else return false;
    }
    char inspect = str.at(0);

    size_t i = 0;
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

    if (!str.empty()) inspect = str.at(0);

    trie_node *node = trie.root;

    size_t i = 0;
    while (i <= num_chars) {
        if (node->children[i] == nullptr) {
            // no matching children
            node->children[i] = new trie_node();
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
    if (str.empty()) {
        return node->is_terminal;
    }

    char inspect = str.at(0);
    for (auto &child : node->children) {
        if (child == nullptr) return false;
        if (child->payload == inspect) {
            return contains(child, str.substr(1, str.size()));
        }
    }
    return false;
}

bool contains(const trie &trie, const std::string &str) {
    char inspect = 0;
    if (trie.size == 0) return false;
    if (!str.empty()) inspect = str.at(0);

    trie_node *node = trie.root;

    for (auto &child : node->children) {
        if (child == nullptr) return false;
        if (child->payload == inspect) {
            if (inspect == 0) return true;
            return contains(child, str.substr(1, str.size()));
        }
    }
    return false;
}

void insert_all(trie &trie, const std::vector<std::string> &items) {
    for (const auto &item : items) {
        insert(trie, item);
    }
}

void init(trie &trie) {
    trie.root = new trie_node;
}

// get index of equal char
bool erase(trie_node *node, const std::string &str, size_t index) {
    if (index+1 == str.size()) {
        // in important node
        if (node->is_terminal) {
            node->is_terminal = false;
            return true;
        } else return false;
    }

    size_t i = 0;
    while (i < num_chars) {
        if (node->children[i] == nullptr) {
            return false;
        } else if (node->children[i]->payload == str[index + 1]) {
            return erase(node->children[i], str, index + 1);
        }
        ++i;
    }
    return false;
}

bool erase(trie &trie, const std::string &str) {
    size_t i = 0;
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