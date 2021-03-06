#include "vector.hpp"
#include "array.hpp"

#include <algorithm>
#include <ostream>

vector::vector():
    m_data(nullptr),
    m_capacity(0),
    m_size(0) {
}

vector::vector(size_t sz, double val) :
    m_data(new double[sz]),
    m_capacity(sz),
    m_size(sz) {
    std::fill_n(m_data.get(), sz, val);
}

vector::vector(const vector& rhs) :
    m_data(new double[rhs.m_size]),
    m_capacity(rhs.m_size),
    m_size(rhs.m_size) {
    copy_array(rhs.m_data.get(), m_data.get(), m_size);
}

vector::vector(vector&& rhs) :
    m_data(std::move(rhs.m_data)),
    m_capacity(rhs.m_capacity),
    m_size(rhs.m_size) {
    rhs.m_data = nullptr;
    rhs.m_capacity = 0;
    rhs.m_size = 0;
}

vector& vector::operator=(const vector& rhs) {
    resize(rhs.m_size);
    copy_array(rhs.m_data.get(), m_data.get(), m_size);
    return *this;
}

vector& vector::operator=(vector&& rhs) {
    m_data = std::move(rhs.m_data);
    m_size = rhs.m_size;
    m_capacity = rhs.m_capacity;
    rhs.m_size = 0;
    rhs.m_capacity = 0;
    return *this;
}

void vector::reserve(size_t cap) {
    if (m_capacity < cap) {
        resize_array(m_data, m_size, cap);
        m_capacity = cap;
    }
}

void vector::push_back(double val) {
    if (m_size == m_capacity) {
        reserve((m_capacity + 1) * 2);
    }

    m_data[m_size] = val;
    m_size++;
}

void vector::pop_back() {
    m_size--;
}

size_t vector::size() const {
    return m_size;
}

size_t vector::capacity() const {
    return m_capacity;
}

void vector::clear() {
    m_size = 0;
}

double& vector::at(size_t i) {
    return m_data[i];
}

double vector::at(size_t i) const {
    return m_data[i];
}

void vector::resize(size_t size, double value) {
    if (size >= m_size) {
        reserve(size);
        std::fill(m_data.get() + m_size, m_data.get() + size, value);
    }

    m_size = size;
}

void vector::swap(vector &rhs) {
    std::swap(m_data, rhs.m_data);
    std::swap(m_size, rhs.m_size);
    std::swap(m_capacity, rhs.m_capacity);
}

T_vectorData vector::operator[](std::size_t index) const {
    if (index < m_size) {
        return m_data[index];
    }
}

std::ostream &vector::operator<<(std::ostream &out, const vector &v) {
    out << "capacity: " << m_capacity;
    out << "size: " << m_size;
    size_t index = 0;
    size_t index_max = v.size() - 1;
    while (index < index_max) {
        out << v[index] << ", ";
        ++index;
    }
    out << std::endl;
}

