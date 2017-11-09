#include "trie.hpp"

#include <utility>
#include <algorithm>

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
        insert1(m_root, s);
    }
}

trie::~trie() {
    deallocate(m_root);
}

bool trie::insert(const std::string& str) {
    if (insert1(m_root, str)) {
        m_size++;
        return true;
    } else return false;
}

bool trie::contains(const std::string& str) const {
    return contains1(m_root, str);
}

bool trie::erase(const std::string &str) {
    if (erase1(m_root, str, 0)) {
        m_size--;
        return true;
    } else return false;
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

// TODO: init to root
word_cursor trie::get_word_cursor() const {
    return word_cursor(m_root);
}

bool word_cursor::has_word() const {
    if (m_ptr->parent != nullptr) {
        return has_word1(m_ptr, nullptr);
    } else {
        // pointer after init in root
        return m_ptr->children[0] != nullptr;
    }
}

std::string word_cursor::read_word() const {
    return {};
}

void word_cursor::move_to_next_word() {
    m_ptr = m_ptr->children[0];
}

word_cursor::word_cursor(const trie_node* ptr) :
    m_ptr(ptr)
{
}
