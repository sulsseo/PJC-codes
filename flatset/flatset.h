#include <stdio.h>
#include <iterator>

using namespace std;

/**
 * Note that when the value of an element is changed so that the comparator orders it differently, the behavior is undefined.
 */
template <typename T, typename Comparator = std::less>
// TODO use default value of unspecified Comparator


class flat_set {
private:
    T *data;
    size_t m_size;
    size_t m_capacity;
    Comparator m_comparator;

public:
    // These types need to be accesible from the outside:
    // iterator
    using iterator = std::iterator;
    // const_iterator
    using const_iterator = std::iterator;
    // size_type
    using size_type = size_t;
    // value_type
    using value_type = T;


    // Special member functions
    flat_set() : m_size(0), m_capacity(10) {}

    flat_set(Comparator const& cmp) : m_size(0), m_capacity(10), m_comparator(cmp) { }

    // TODO: deep copy constructor
    flat_set(flat_set const& rhs) { }

    flat_set(flat_set && rhs) : m_size(rhs.size), m_capacity(rhs.capacity), m_comparator(rhs.m_comparator) {
    }

    flat_set& operator=(flat_set const& rhs);
    flat_set& operator=(flat_set && rhs);
    ~flat_set();
    // Constructs flat_set from elements in range [first, last)
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last);
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last, Comparator const& cmp);


    // Insert overloads
    std::pair<iterator, bool> insert(T const& v);
    std::pair<iterator, bool> insert(T&& v);
    // Inserts [first, last) range of elements
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last);

    // Erase overloads
    // Deletes element pointed-to by i, returns iterator to the next element
    iterator erase(const_iterator i);
    // Deletes elements in range [first, last), returns iterator to the next element
    iterator erase(const_iterator first, const_iterator last);
    // Deletes element equal to key if it is present, returns how many elements were deleted
    size_type erase(value_type const& key);

    // Iterator member functions
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    // The usual queries
    bool empty() const { return m_size == 0; }
    size_type size() const { return m_size; }
    size_type capacity() const { return m_capacity; }

    void reserve(size_type c);
    void clear();

    // Lookup member functions
    // Returns iterator to element equivalent to v, or an end iterator if such element is not present
    iterator find(T const& v);
    const_iterator find(T const& v) const;

    // Returns iterator to first element that is not less than t, end iterator if no such element is present
    iterator lower_bound(T const& t);
    const_iterator lower_bound(T const& t) const;

    // Returns iterator to first element that is greater than t, end iterator if no such element is present
    iterator upper_bound(T const& t);
    const_iterator upper_bound(T const& t) const;

    void swap(flat_set& o);
};

// Lexicographical comparisons
bool operator==(flat_set const& a, flat_set const& b);
bool operator!=(flat_set const& a, flat_set const& b);
bool operator<(flat_set const& a, flat_set const& b);
bool operator<=(flat_set const& a, flat_set const& b);
bool operator>=(flat_set const& a, flat_set const& b);
bool operator>(flat_set const& a, flat_set const& b);

template <typename T>
void swap(flat_set<T> const& a, flat_set<T> const& b);