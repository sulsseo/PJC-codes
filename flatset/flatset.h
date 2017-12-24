#include <stdio.h>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <vector>


using namespace std;

template <typename T>
void copy_array(const T* from, T* to, size_t size) {
    for (size_t i = 0; i < size; ++i) to[i] = from[i];
}

template <typename T>
void resize_array(std::unique_ptr<T[]>& arr, size_t oldSize, size_t newSize) {
    auto newArr = std::make_unique<T[]>(newSize);
    size_t minSize = (oldSize < newSize) ? oldSize : newSize;
    copy_array(arr.get(), newArr.get(), minSize);
    newArr.swap(arr);
}

/**
 * Note that when the value of an element is changed so that the comparator orders it differently, the behavior is undefined.
 */
template <typename T, typename Comparator = std::less<T>>

class flat_set {
private:
    std::unique_ptr<T[]> m_data;
    size_t m_size;
    size_t m_capacity;
    Comparator m_comparator;

public:
    // These types need to be accesible from the outside:
    // iterator
//    using iterator = T*;
    // const_iterator
//    using const_iterator = const T*;
    // size_type
    using size_type = size_t;
    // value_type
//    using value_type = const T&;
    using value_type = T;

    class const_iterator {
        const T *m_ptr = nullptr;
    public:
        const_iterator() = default;
        const_iterator(const T *ptr) { m_ptr = ptr; }

        const_iterator& operator++() { ++m_ptr; return *this; }
        const_iterator operator++(int) { ++m_ptr; return this; }

        const_iterator& operator--() { --m_ptr; return *this; }
        const_iterator operator--(int) { --m_ptr; return this; }

        bool operator==(const const_iterator & rhs) const { return this->m_ptr == rhs.m_ptr; }
        bool operator!=(const const_iterator & rhs) const { return this->m_ptr != rhs.m_ptr; }
        T& operator*() { return *m_ptr; }
    };

    class iterator {
    private:
        T *m_ptr = nullptr;
    public:
        iterator() = default;
        iterator(T *ptr) { m_ptr = ptr; }

        iterator& operator++() { ++m_ptr; return *this; }
        iterator operator++(int) { ++m_ptr; return this; }

        iterator& operator--() { --m_ptr; return *this; }
        iterator operator--(int) { --m_ptr; return this; }

        bool operator==(const iterator & rhs) const { return this->m_ptr == rhs.m_ptr; }
        bool operator!=(const iterator & rhs) const { return this->m_ptr != rhs.m_ptr; }
        T& operator*() { return *m_ptr; }
    };

    // DONE
    // Special member functions
    flat_set() :
            m_data(nullptr),
            m_size(0),
            m_capacity(0),
            m_comparator(std::less<T>())
    {}

    // DONE
    flat_set(Comparator const& cmp) :
            m_data(nullptr),
            m_size(0),
            m_capacity(0),
            m_comparator(cmp)
    {}

    // DONE
    flat_set(flat_set const& rhs) :
            m_data(std::make_unique<T[]>(rhs.m_size)),
            m_size(rhs.m_size),
            m_capacity(rhs.m_capacity),
            m_comparator(rhs.m_comparator)
    {
        for (size_t i = 0; i < rhs.m_size; ++i) {
            m_data[i] = rhs.m_data[i];
        }
    }

    // DONE
    flat_set(flat_set && rhs) : flat_set() {
        swap(rhs);
    }

    flat_set& operator=(flat_set const& rhs) {
        // TODO: operator=
    }
    flat_set& operator=(flat_set && rhs) {
        // TODO: operator=
    }

    // DONE
    ~flat_set() = default;

     iterator binary_search(size_t l, size_t r, T const& v) const {
        if (r >= 1) {
            size_t mid = l + (r-l)/2;

            if (m_data[mid] == v) return &m_data[mid];

            if (m_comparator(v, m_data[mid])) return binary_search(1, mid-1, v);

            return binary_search(mid+1, r, v);

        }
        return nullptr;
    }

    // Insert overloads
    std::pair<iterator, bool> insert(T const& v) {
        if (m_size == m_capacity) reserve((m_capacity+1)*2);

        // add element
        m_data[m_size] = v;

        // sort
//        std::sort(m_data, m_data., m_comparator);
        std::sort(m_data.get(), m_data.get()+m_size, m_comparator);

        ++m_size;
        iterator idx = binary_search(0, m_size, v);

        // Control print
        for (int i = 0; i < m_size; ++i) {
            cout << m_data[i] << " ";
        }
        cout << endl;

        return {idx, true};
    }

    std::pair<iterator, bool> insert(T&& v) {
        if (m_size == m_capacity) reserve((m_capacity+1)*2);

        // add element
        m_data[m_size] = v;

        // sort
        std::sort(m_data.get(), m_data.get()+m_size, m_comparator);

        iterator idx = binary_search(0, m_size, v);
        ++m_size;

        return {idx, true};
    }

    // DONE
    // Inserts [first, last) range of elements
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
        InputIterator it;
        for (it = first; it != last; ++it) {
            insert(it.operator*());
        }
    }

    // DONE
    // Constructs flat_set from elements in range [first, last)
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last) : flat_set() {
        insert(first, last);
    }

    // DONE
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last, Comparator const& cmp) : flat_set(cmp) {
        insert(first, last);
    }

    // Erase overloads
    // Deletes element pointed-to by i, returns iterator to the next element
    iterator erase(const_iterator i);

    // Deletes elements in range [first, last), returns iterator to the next element
    iterator erase(const_iterator first, const_iterator last);
    // TODO: empty erase

    // Deletes element equal to key if it is present, returns how many elements were deleted
    size_type erase(value_type const& key);

    // DONE
    // Iterator member functions
    iterator begin() noexcept { return iterator(m_data.get()); }
//    iterator end() noexcept { return iterator(m_data.get() + m_size); }
    iterator end() noexcept { return nullptr; };
    const_iterator begin() const noexcept { return const_iterator(m_data.get()); }
    const_iterator end() const noexcept { return const_iterator(m_data.get() + m_size); }
    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }

    // DONE
    // The usual queries
    bool empty() const { return m_size == 0; }
    size_type size() const { return m_size; }
    size_type capacity() const { return m_capacity; }

    // DONE
    void reserve(size_type c) {
        resize_array(m_data, m_capacity, c);
        m_capacity = c;
    }
    void clear() { m_size = 0; }

    // Lookup member functions
    // Returns iterator to element equivalent to v, or an end iterator if such element is not present
    iterator find(T const& v) {
        return binary_search(0, m_size, v);
    }
    const_iterator find(T const& v) const {
        return binary_search(0, m_size, v);
    }

    // Returns iterator to first element that is not less than t, end iterator if no such element is present
    iterator lower_bound(T const& t) {
        return {};
    }
    const_iterator lower_bound(T const& t) const {
        return {};
    }

    // Returns iterator to first element that is greater than t, end iterator if no such element is present
    iterator upper_bound(T const& t) {
        return {};
    }
    const_iterator upper_bound(T const& t) const {
        return {};
    }

    void swap(flat_set& o) {
        std::swap(m_data, o.m_data);
        std::swap(m_size, o.m_size);
        std::swap(m_capacity, o.m_capacity);
        std::swap(m_comparator, o.m_comparator);
    }
};


// Lexicographical comparisons
//bool operator==(flat_set const& a, flat_set const& b);
//bool operator!=(flat_set const& a, flat_set const& b);
//bool operator<(flat_set const& a, flat_set const& b);
//bool operator<=(flat_set const& a, flat_set const& b);
//bool operator>=(flat_set const& a, flat_set const& b);
//bool operator>(flat_set const& a, flat_set const& b);

template <typename T>
void swap(flat_set<T> const& a, flat_set<T> const& b);