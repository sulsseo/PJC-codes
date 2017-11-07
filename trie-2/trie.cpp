#include "trie.hpp"
//#include "trie-1.hpp"

#include <utility>
#include <algorithm>

trie::trie() {
    m_root = new trie_node;
    m_size = 0;
}

trie::trie(const std::vector<std::string>& strings) {
    m_root = new trie_node;
    m_size = strings.size();
//    insert_all(*m_root, strings);
    // TODO: insert by for with inserts
}

trie::~trie() {
    deallocate(m_root);
}

bool trie::insert(const std::string& str) {
    return insert1(m_root, str);
}

bool trie::contains(const std::string& str) const {
    return contains1(m_root, str);
}

bool trie::erase(const std::string &str) {
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

word_cursor trie::get_word_cursor() const {
    return {};
}


bool word_cursor::has_word() const {
    return false;
}

std::string word_cursor::read_word() const {
    return {};
}

void word_cursor::move_to_next_word() {}

word_cursor::word_cursor(const trie_node* ptr) {
    m_ptr = ptr;
}
