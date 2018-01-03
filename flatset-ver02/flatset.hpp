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

    using base = std::vector<T>;

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

    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
        reserve(m_data.capacity() + std::distance(first, last));

        std::vector<T> tmp(first, last);
        std::sort(tmp.begin(), tmp.end(), m_comp);
        auto it = tmp.begin();
        auto inspect = tmp.end();

        while (it != tmp.end()) {
            if (!equal(*inspect, *it)) {
                m_data.push_back(*it);
                inspect = it;
            }
            ++it;
        }

        while (first != last) {
            auto it = find(*first);
            if (it == end()) m_data.push_back(*first);
            ++first;
        }

        std::sort(begin(), end(), m_comp);
    }

    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last, std::input_iterator_tag) {
        std::vector<T> tmp(first, last);
        std::sort(tmp.begin(), tmp.end(), m_comp);
        auto it = tmp.begin();
        auto inspect = tmp.end();

        while (it != tmp.end()) {
            if (!equal(*inspect, *it)) {
                m_data.push_back(*it);
                inspect = it;
            }
            ++it;
        }

        while (first != last) {
            auto it = find(*first);
            if (it == end()) m_data.push_back(*first);
            ++first;
        }

        std::sort(begin(), end(), m_comp);
    }

    template <typename ForwardIterator>
    void insert(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) {
        reserve(m_data.capacity() + std::distance(first, last));

        std::vector<T> tmp(first, last);
        std::sort(tmp.begin(), tmp.end(), m_comp);
        auto it = tmp.begin();
        auto inspect = tmp.end();

        while (it != tmp.end()) {
            if (!equal(*inspect, *it)) {
                m_data.push_back(*it);
                inspect = it;
            }
            ++it;
        }

        while (first != last) {
            auto it = find(*first);
            if (it == end()) m_data.push_back(*first);
            ++first;
        }

        std::sort(begin(), end(), m_comp);
    }


    // Inserts [first, last) range of elements


    // Constructs flat_set from elements in range [first, last)
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last) : m_data(), m_comp() {
//        reserve(500'000);
////        cout << last - first;
//        for (InputIterator it = first; it != last ; ++it) {
////            insert(*it);
////            auto iter = find(*it);
////            if (iter == end()) {
//                m_data.push_back(std::move(*it));
////            }
//        }
//        std::sort(m_data.begin(), m_data.end(), m_comp);
//        insert(first, last, typename std::iterator_traits<InputIterator>::iterator_category{});
        insert(first, last);
    }
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last, Comparator const& cmp) : flat_set(cmp) {
//        reserve(500'000);
//        for (InputIterator it = first; it != last ; ++it) {
////            insert(*it);
////            auto iter = find(*it);
////            if (iter == end()) {
//                m_data.push_back(std::move(*it));
////            }
//        }
//        std::sort(m_data.begin(), m_data.end(), cmp);
//        insert(first, last, typename std::iterator_traits<InputIterator>::iterator_category{});
        insert(first, last);
    }

    // Insert overloads
    std::pair<iterator, bool> insert(T const& v) {
        auto it = find(v);
        if (it != m_data.end()) return  {it, false};

        it = m_data.insert(m_data.end(), v);

        std::sort(m_data.begin(), m_data.end(), m_comp);

        return {end(), true};
    };

    std::pair<iterator, bool> insert(T&& v) {
        auto it = find(v);
        if (it != m_data.end()) return  {it, false};

        it = m_data.insert(m_data.end(), std::move(v));

        std::sort(m_data.begin(), m_data.end(), m_comp);

        return {it, true};
    };

    // Erase overloads
    // Deletes element pointed-to by i, returns iterator to the next element
    iterator erase(const_iterator i) {
//        auto it = m_data.erase(i);
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

    iterator binary_search(int l, int r, T const& x) {

        if (r >= l) {
            int mid = l + (r - l)/2;

            if (equal(x, m_data[mid]))  return {m_data.begin()+mid};

            if (m_comp(x, m_data[mid])) return binary_search(l, mid-1, x);

            return binary_search(mid+1, r, x);
        }

        return {end()};
    }

    const_iterator binary_search(int l, int r, T const& x) const {

        if (r >= l) {
            int mid = l + (r - l)/2;

            if (equal(x, m_data[mid]))  return {m_data.begin()+mid};

            if (m_comp(x, m_data[mid])) return binary_search(l, mid-1, x);

            return binary_search(mid+1, r, x);
        }

        return {end()};
    }

    // Lookup member functions
    // Returns iterator to element equivalent to v, or an end iterator if such element is not present
    iterator find(T const& v) {

        if (m_data.size() == 0) return end();
        else if(m_data.size() == 1) {
            if (equal(*begin(),v)) return begin();
            else return end();
        } else return binary_search(0,m_data.size(),v);

//        auto it = m_data.begin();
//        auto end = m_data.end();
//
//        while (it != end) {
//            if (equal(*it, v)) {
//                return it;
//            }
//            ++it;
//        }
//        return it;
    }
    const_iterator find(T const& v) const {
//        auto it = m_data.begin();
//        auto end = m_data.end();
//        while (it != end) {
//            if (equal(*it, v)) {
//                return it;
//            }
//            ++it;
//        }
//        return it;
        if (m_data.size() == 0) return end();
        else if(m_data.size() == 1) {
            if (equal(*begin(),v)) return begin();
            else return end();
        } else return binary_search(0,m_data.size(),v);
    }

    // Returns iterator to first element that is not less than t, end iterator if no such element is present
    iterator lower_bound(T const& t) {
        auto it = end();
        auto first = begin();

        if (*first > t) return begin();
        if (*(--it) < t) return end();

        while (*first < t) {
            ++first;
        }
        return first;
    }
    const_iterator lower_bound(T const& t) const {
        auto it = end();
        auto first = begin();

        if (*first > t) return begin();
        if (*(--first) < t) return end();

        while (*first < t) {
            ++first;
        }
        return first;
    }

    // Returns iterator to first element that is greater than t, end iterator if no such element is present
    iterator upper_bound(T const& t) {
        auto it = begin();
        while (*it <= t) {
            ++it;
        }
        return it;
    }
    const_iterator upper_bound(T const& t) const {
        auto it = begin();
        while (*it <= t) {
            ++it;
        }
        return it;
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