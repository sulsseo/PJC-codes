#include "trie.hpp"

#include <utility>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

trie::trie() :
    m_root(new trie_node),
    m_size(0)
{

}

trie::trie(const std::vector<std::string>& strings) :
    m_root(new trie_node),
    m_size(0)
{
    for (std::string s : strings) {
        insert(s);
    }
}

void deallocate(trie_node *node) {
    for (trie_node *&child : node->children) {
        if (child != nullptr) {
            deallocate(child);
        } else break;
    }
    delete node;
}

trie::~trie() {
    deallocate(m_root);
}

bool insert1(trie_node *node, std::string str) {
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
            return insert1(node->children[i], str.substr(1, str.size()));
        } else if (node->children[i]->payload == inspect)
            return insert1(node->children[i], str.substr(1, str.size()));
        ++i;
    }
    return false;
}

bool trie::insert(const std::string& str) {
    char inspect = 0;

    if (!str.empty()) inspect = str.at(0);

    size_t i = 0;
    while (i <= num_chars) {
        if (m_root->children[i] == nullptr) {
            // no matching children
            m_root->children[i] = new trie_node();
            m_root->children[i]->payload = inspect;
            m_root->children[i]->parent = m_root;
            if (inspect == 0) {
                m_root->children[i]->is_terminal = true;
                m_size++;
                return true;
            }
            if (insert1(m_root->children[i], str.substr(1, str.size()))) {
                m_size++;
                return true;
            } else return false;
        } else if (m_root->children[i]->payload == inspect) {
            if (insert1(m_root->children[i], str.substr(1, str.size()))) {
                m_size++;
                return true;
            } else return false;
        }
        ++i;
    }
    return false;
}

bool contains1(trie_node *node, std::string str) {
    if (str.empty()) {
        return node->is_terminal;
    }

    char inspect = str.at(0);
    for (auto &child : node->children) {
        if (child == nullptr) return false;
        if (child->payload == inspect) {
            return contains1(child, str.substr(1, str.size()));
        }
    }
    return false;
}

bool trie::contains(const std::string& str) const {
    char inspect = 0;
    if (m_size == 0) return false;
    if (!str.empty()) inspect = str.at(0);

    for (auto &child : m_root->children) {
        if (child == nullptr) return false;
        if (child->payload == inspect) {
            if (inspect == 0) return true;
            return contains1(child, str.substr(1, str.size()));
        }
    }
    return false;
}

bool erase1(trie_node *node, const std::string &str, size_t index) {
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
            return erase1(node->children[i], str, index + 1);
        }
        ++i;
    }
    return false;
}

bool trie::erase(const std::string &str) {
    size_t i = 0;
    while (i <= num_chars) {
        if (m_root->children[i] == nullptr) {
            return false;
        } else if (m_root->children[i]->payload == str[0]) {
            // got child
            if (erase1(m_root->children[i], str, 0)) {
                m_size--;
                return true;
            } else return false;
        }
        ++i;
    }
    return false;
}

size_t trie::size() const {
    return m_size;
}

bool trie::empty() const {
    return m_size == 0;
}


std::vector<std::string> trie::search_by_prefix(const std::string& str) const {
    return {};
}

std::vector<std::string> trie::get_prefixes(const std::string& str) const {
    return {};
}

// DONE
word_cursor trie::get_word_cursor() const {
    return word_cursor(m_root);
}

/*
 * PRE-order searching strategy
 */
bool has_word1(const trie_node *node, const trie_node *prev, const trie_node *ptr) {
    // is terminal, not current and visited on way down
    if (node->is_terminal && node != ptr && prev == nullptr) return true;

    if (prev == nullptr) {
        // go down
        for (auto child : node->children) {
            if (child == nullptr) {
                break;
            } else {
                return has_word1(child, nullptr, ptr);
            }
        }
        if (node->parent != nullptr) {
            return has_word1(node->parent, node, ptr);
        } else return false;

    } else {
        // go up
        bool after_from_node = false;
        for (auto child : node->children) {
            if (child == prev) {
                after_from_node = true;
            } else if (child != nullptr && after_from_node) {
                // be sure its next after already known subtree
                return has_word1(child, nullptr, ptr);
            }
        }
        if (node->parent != nullptr) {
            return has_word1(node->parent, node, ptr);
        } else return false;
    }
}


// DONE
bool word_cursor::has_word() const {
    return m_ptr != nullptr;
}

std::vector<char> read_word1(const trie_node *node, std::vector<char> &word) {
    if (node->parent != nullptr) {
        word.insert(word.begin(), node->payload);
        return read_word1(node->parent, word);
    } else {
        return word;
    }
}

// DONE
std::string word_cursor::read_word() const {
    std::vector<char> word;
    read_word1(m_ptr, word);
    std::stringstream ss;

    if (word[0] == 0) return "";

    for (int i = 0; i < word.size(); ++i) {
        ss << word[i];
    }
    return ss.str();
}

/*
 * when go down:    go to most left child, prev == nullptr
 * when go up:      go to parent, prev == from node
 */
const trie_node* move_to_next_word1(const trie_node *node, const trie_node *prev, const trie_node* ptr) {

    if (node->is_terminal && node != ptr && prev == nullptr) return node;

    if (prev == nullptr) {
        // go down
        for (auto child : node->children) {
            if (child == nullptr) {
                break;
            } else {
                return move_to_next_word1(child, nullptr, ptr);
            }
        }
        if (node->parent != nullptr) {
            return move_to_next_word1(node->parent, node, ptr);
        } else return nullptr;

    } else {
        // go up
        bool after_from_node = false;
        for (auto child : node->children) {
            if (child == prev) {
                after_from_node = true;
            } else if (child != nullptr && after_from_node) {
                // be sure its next after already known subtree
                return move_to_next_word1(child, nullptr, ptr);
            }
        }
        if (node->parent != nullptr) {
            return move_to_next_word1(node->parent, node, ptr);
        } else return nullptr;
    }
}

void word_cursor::move_to_next_word() {
    if (m_ptr->parent != nullptr) {
        // inside trie
        m_ptr = move_to_next_word1(m_ptr, nullptr, m_ptr);
    } else if (m_ptr->parent == nullptr && m_ptr->children[0] != nullptr) {
        // in root and have child
        m_ptr = move_to_next_word1(m_ptr->children[0], nullptr, m_ptr);
    } else {
        cerr << "no way..." << endl;
    }
}

word_cursor::word_cursor(const trie_node* ptr) :
    m_ptr(ptr)
{
    move_to_next_word();
}
