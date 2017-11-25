#include <sstream>
#include <algorithm>
#include "trie.hpp"

/*********************** Trie methods ***************************/

bool erase1(trie_node *node, const std::string &str, size_t index) {
    if (index + 1 == str.size()) {
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

bool trie::insert(const std::string &str) {
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

bool trie::contains(const std::string &str) const {
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

trie_node *deep_copy(trie_node *parent, trie_node *node) {
    auto copy_node = new trie_node;
    copy_node->payload = node->payload;
    copy_node->is_terminal = node->is_terminal;
    copy_node->parent = parent;

    for (int i = 0; i < num_chars; ++i) {
        if (node->children[i] == nullptr) break;
        copy_node->children[i] = deep_copy(copy_node, node->children[i]);
    }

    return copy_node;
}

/**************************************************/

trie::trie() :
        m_root(new trie_node),
        m_size(0) {
}

trie::trie(const std::vector<std::string> &strings) :
        m_root(new trie_node),
        m_size(0) {
    for (const std::string &s : strings) {
        insert(s);
    }
}

// copy constructor
trie::trie(const trie &rhs) :
        m_root(nullptr),
        m_size(rhs.m_size) {
    m_root = deep_copy(nullptr, rhs.m_root);
}

trie::trie(trie &&rhs) : trie() {
    swap(rhs);
}

trie &trie::operator=(const trie &rhs) {
    trie tmp(rhs);
    swap(tmp);
    return *this;
}

trie &trie::operator=(trie &&rhs) {
    swap(rhs);
    return *this;
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

/**************************************************/

size_t trie::size() const {
    return m_size;
}

bool trie::empty() const {
    return m_size == 0;
}

void search_by_prefix1(const trie_node *node,
                       const std::string &str,
                       const std::string &word,
                       std::vector<std::string> &storage) {

    if (str.size() <= word.size()) {
        if (node->is_terminal && !word.empty()) {
            storage.push_back(word);
        }
        for (trie_node *child : node->children) {
            if (child != nullptr) {
                search_by_prefix1(child, str, word + child->payload, storage);
            } else return;
        }
    } else {
        for (trie_node *child : node->children) {
            if (child == nullptr) return;
            else if (child->payload == str[word.size()]) {
                search_by_prefix1(child, str, word + child->payload, storage);
            }
        }
    }
}

std::vector<std::string> trie::search_by_prefix(const std::string &str) const {
    std::string word;
    std::vector<std::string> storage;

    for (trie_node *child : m_root->children) {
        if (child == nullptr) {
            break;
        } else if (str.empty()) {
            word += child->payload;
            search_by_prefix1(child, str, word, storage);
        } else if (child->payload == str[0]) {
            word += child->payload;
            search_by_prefix1(child, str, word, storage);
            break;
        }
    }

    return storage;
}

void get_prefixes1(const trie_node *node,
                   const std::string &str,
                   const std::string &pref,
                   std::vector<std::string> &storage) {
    if (str.size() >= pref.size()) {
        if (node->is_terminal && !pref.empty()) {
            storage.push_back(pref);
        }
        for (trie_node *child : node->children) {
            if (child == nullptr) break;
            else if (child->payload == str[pref.size()]) {
                get_prefixes1(child, str, pref + child->payload, storage);
            }
        }
    } else return;
}

std::vector<std::string> trie::get_prefixes(const std::string &str) const {
    std::vector<std::string> storage;
    std::string pref;

    for (trie_node *child : m_root->children) {
        if (child == nullptr || str.empty()) {
            break;
        } else if (child->payload == str[0]) {
            pref += child->payload;
            get_prefixes1(child, str, pref, storage);
            break;
        }
    }

    return storage;
}

/**************************************************/


/**
 * move through trie structure
 *
 * @param node inspected node
 * @param prev previous node which pointer go from
 * @param ptr start pointer
 * @param idx step size
 * @return node where some word ends
 */
const trie_node *move(const trie_node *node, const trie_node *prev, const trie_node *ptr, size_t idx) {

    if (node->is_terminal && node != ptr && prev == nullptr) {
        if (idx == 0) {
            return node;
        } else {
            idx--;
        }
    }

    if (prev == nullptr) {
        // go down
        for (trie_node *child : node->children) {
            if (child == nullptr) {
                break;
            } else {
                return move(child, nullptr, ptr, idx);
            }
        }
        if (node->parent != nullptr) {
            return move(node->parent, node, ptr, idx);
        } else return nullptr;

    } else {
        // go up
        bool after_from_node = false;
        for (trie_node *child : node->children) {
            if (child == prev) {
                after_from_node = true;
            } else if (child != nullptr && after_from_node) {
                // be sure its next after already known subtree
                return move(child, nullptr, ptr, idx);
            }
        }
        if (node->parent != nullptr) {
            return move(node->parent, node, ptr, idx);
        } else return nullptr;
    }
}

// DONE
trie::const_iterator trie::begin() const {
    const trie_node *ptr = move(m_root, nullptr, nullptr, 0);
    return {ptr};
}

// DONE
trie::const_iterator trie::end() const {
    return {nullptr};
}

// DONE
void trie::swap(trie &rhs) {
    std::swap(m_root, rhs.m_root);
    std::swap(m_size, rhs.m_size);
}

/**************************************************/

void read_word1(const trie_node *node, std::vector<char> &word) {
    if (node->parent != nullptr) {
        word.insert(word.begin(), node->payload);
        read_word1(node->parent, word);
    } else return;
}

std::string read_word(const trie_node *node) {
    std::vector<char> word;
    read_word1(node, word);
    std::stringstream ss;

    if (word[0] == 0) return "";

    for (char letter : word) {
        ss << letter;
    }

    return ss.str();
}

std::vector<std::string> read_trie_dict(const trie_node *t) {
    std::vector<std::string> storage;

    while (true) {
        t = move(t, nullptr, t, 0);
        if (t == nullptr) break;

        storage.push_back(read_word(t));
    }

    return storage;
}

// DONE
bool trie::operator==(const trie &rhs) const {
    if (m_size != rhs.m_size) return m_size == 0;

    std::vector<std::string> t1 = read_trie_dict(m_root);
    std::vector<std::string> t2 = read_trie_dict(rhs.m_root);

    // sort resulting lists
    sort(t1.begin(), t1.end());
    sort(t2.begin(), t2.end());

    return t1 == t2;
}

bool trie::operator<(const trie &rhs) const {
    return false;
}

trie trie::operator&(trie const &rhs) const {
    std::vector<std::string> v;
    std::vector<std::string> t1 = {begin(), end()};
    std::vector<std::string> t2 = {rhs.begin(), rhs.end()};
    
    std::sort(t1.begin(), t1.end());
    std::sort(t2.begin(), t2.end());

    std::set_intersection(t1.begin(), t1.end(), t2.begin(), t2.end(), back_inserter(v));

    return {v};
}

trie trie::operator|(trie const &rhs) const {
    std::vector<std::string> v;
    std::vector<std::string> t1 = {begin(), end()};
    std::vector<std::string> t2 = {rhs.begin(), rhs.end()};

    std::sort(t1.begin(), t1.end());
    std::sort(t2.begin(), t2.end());

    std::set_union(t1.begin(), t1.end(), t2.begin(), t2.end(), back_inserter(v));

    return {v};
}

bool operator!=(const trie &lhs, const trie &rhs) {
    return !(lhs == rhs);
}

bool operator>(const trie &lhs, const trie &rhs) {
    return rhs < lhs;
}

bool operator<=(const trie &lhs, const trie &rhs) {
    return !(lhs > rhs);
}

bool operator>=(const trie &lhs, const trie &rhs) {
    return !(lhs < rhs);
}

void swap(trie &lhs, trie &rhs) {
    lhs.swap(rhs);
}

std::ostream &operator<<(std::ostream &out, trie const &trie) {
    out << "size: " << trie.size();
    return out;
}

/**************************************************/

trie::const_iterator &trie::const_iterator::operator++() {
    current_node = move(current_node, nullptr, current_node, 0);
    return *this;
}

trie::const_iterator trie::const_iterator::operator++(int) {
    current_node = move(current_node, nullptr, current_node, 0);
    return *this;
}

trie::const_iterator::const_iterator(const trie_node *node) {
    current_node = node;
}

bool trie::const_iterator::operator==(const trie::const_iterator &rhs) const {
    return current_node == rhs.current_node;
}

bool trie::const_iterator::operator!=(const trie::const_iterator &rhs) const {
    return current_node != rhs.current_node;
}

trie::const_iterator::reference trie::const_iterator::operator*() const {
    std::string word = read_word(current_node);
    return word;
}
