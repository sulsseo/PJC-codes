#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * Note that when the value of an element is changed so that the comparator orders it differently, the behavior is undefined.
 */
template<typename T, typename Comparator = std::less<T>>
class flat_set {
public:
    // These types need to be accesible from the outside:
    // iterator
    // const_iterator

    typedef T value_type;
    typedef size_t size_type;

    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    // Special member functions
    flat_set() : m_data(), m_comp() {}

    flat_set(Comparator const& cmp) : flat_set() {
        m_comp = cmp;
    }

    flat_set(flat_set const& rhs) : flat_set(rhs.m_comp) {
        for (size_t i = 0; i < rhs.m_data.size(); ++i) {
            m_data.push_back(rhs.m_data[i]);
        }
    }

    flat_set(flat_set && rhs) : flat_set() {
        swap(rhs);
    }

    flat_set& operator=(flat_set const& rhs) {
        m_data = std::move(rhs.m_data);
        m_comp = rhs.m_comp;
        return *this;
    }

    flat_set& operator=(flat_set && rhs) {
        m_data = std::move(rhs.m_data);
        m_comp = rhs.m_comp;
        return *this;
    }

    ~flat_set() = default;

    bool empty() const { return m_data.empty(); }
    size_type size() const { return m_data.size(); }
    size_type capacity() const { return m_data.capacity(); }

    void reserve(size_type c) { m_data.reserve(c); }
    void clear() { m_data.clear(); }

    // Inserts [first, last) range of elements
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
        insert(first, last, typename std::iterator_traits<InputIterator>::iterator_category{});
    }

    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last, std::input_iterator_tag) {
        while(first != last) {
            insert(*first);
            ++first;
        }
    }

    template <typename ForwardIterator>
    void insert(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) {
        m_data.reserve(m_data.size() + std::distance(first, last));

        while(first!=last) {
            insert(*first);
            ++first;
        }
    }

    // Constructs flat_set from elements in range [first, last)
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last) : m_data(first, last) {
        std::sort(m_data.begin(), m_data.end(), m_comp);
        m_data.erase(std::unique(m_data.begin(), m_data.end(), [&](T const & l, T const& r){
            return !m_comp(l, r) && !m_comp(r, l);
        }), m_data.end());
    }
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last, Comparator const& cmp) : flat_set(cmp) {
        insert(first, last, typename std::iterator_traits<InputIterator>::iterator_category{});
    }

    // Insert overloads
    std::pair<iterator, bool> insert(T const& v) {
        iterator it;
        iterator lb = std::lower_bound(m_data.begin(), m_data.end(), v, m_comp);

        if (lb != m_data.end() && !m_comp(v, *lb)) it = lb;
        else it = end();

        if (it != m_data.end()) return {it, false};

        it = m_data.insert(lb, v);

        return {it, true};
    };

    std::pair<iterator, bool> insert(T&& v) {
        iterator it;
        iterator lb = std::lower_bound(m_data.begin(), m_data.end(), v, m_comp);

        if (lb != m_data.end() && !m_comp(v, *lb)) it = lb;
        else it = end();

        if (it != m_data.end()) return {it, false};

        it = m_data.insert(lb, std::move(v));

        return {it, true};
    };

    // Erase overloads
    // Deletes element pointed-to by i, returns iterator to the next element
    iterator erase(const_iterator i) {
        return m_data.erase(i);
    }
    // Deletes elements in range [first, last), returns iterator to the next element
    iterator erase(const_iterator first, const_iterator last) {
        return m_data.erase(first, last);
    }
    // Deletes element equal to key if it is present, returns how many elements were deleted
    size_type erase(value_type const& key) {
        auto it = find(key);
        if (it == end()) return 0;

        m_data.erase(it);

        return 1;
    }

    // Iterator member functions
    iterator begin() noexcept { return m_data.begin(); }
    iterator end() noexcept { return m_data.end(); }
    const_iterator begin() const noexcept { return m_data.begin(); }
    const_iterator end() const noexcept { return m_data.end(); }
    const_iterator cbegin() const noexcept { return m_data.cbegin(); }
    const_iterator cend() const noexcept { return m_data.cend(); }


    bool equal(T const& a, T const& b) const {
        return !m_comp(a, b) && !m_comp(b, a);
    }

    // Lookup member functions
    // Returns iterator to element equivalent to v, or an end iterator if such element is not present
    iterator find(T const& v) {
        iterator first = std::lower_bound(m_data.begin(), m_data.end(), v, m_comp);
        if (first != m_data.end() && !m_comp(v, *first)) return first;
        else return end();
    }
    const_iterator find(T const& v) const {
        iterator first = lower_bound(v);
        if (first != end() && !m_comp(v, *first)) return first;
        else return end();
    }

    // Returns iterator to first element that is not less than t, end iterator if no such element is present
    iterator lower_bound(T const& t) {
        return std::lower_bound(m_data.begin(), m_data.end(), t, m_comp);
    }
    const_iterator lower_bound(T const& t) const {
        return std::lower_bound(m_data.begin(), m_data.end(), t, m_comp);
    }

    // Returns iterator to first element that is greater than t, end iterator if no such element is present
    iterator upper_bound(T const& t) {
        return std::upper_bound(m_data.begin(), m_data.end(), t, m_comp);
    }
    const_iterator upper_bound(T const& t) const {
        return std::upper_bound(m_data.begin(), m_data.end(), t, m_comp);
    }

    void swap(flat_set& o) {
        std::swap(m_data, o.m_data);
        std::swap(m_comp, o.m_comp);
    }

    std::vector<T> m_data;
    Comparator m_comp;
};


// Lexicographical comparisons
template <typename T>
bool operator==(flat_set<T> const& a, flat_set<T> const& b) { return a.m_data == b.m_data; }

template <typename T>
bool operator!=(flat_set<T> const& a, flat_set<T> const& b) { return a.m_data != b.m_data; }

template <typename T>
bool operator<(flat_set<T> const& a, flat_set<T> const& b) { return a.m_data < b.m_data; }

template <typename T>
bool operator<=(flat_set<T> const& a, flat_set<T> const& b) { return a.m_data <= b.m_data; }

template <typename T>
bool operator>=(flat_set<T> const& a, flat_set<T> const& b) { return a.m_data >= b.m_data; }

template <typename T>
bool operator>(flat_set<T> const& a, flat_set<T> const& b) { return a.m_data > b.m_data; }

template <typename T>
void swap(flat_set<T> const& a, flat_set<T> const& b) {
    flat_set<T> tmp(a);
    a = b;
    b = tmp;
}