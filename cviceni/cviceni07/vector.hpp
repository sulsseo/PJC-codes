#pragma once
#include <cstddef>
#include <memory>
#include <iosfwd>
#include "vector.hpp"

using std::size_t;

typedef double T_vectorData;

class vector {
public:
    vector();
    vector(size_t sz, double val);

    vector(const vector& rhs);
    vector(vector&& rhs);
    vector& operator=(const vector& rhs);
    vector& operator=(vector&& rhs);
    T_vectorData operator[](std::size_t index) const;

    void reserve(size_t cap);
    void resize(size_t sz, double val = 0);
    void push_back(double val);
    void pop_back();
    size_t size() const;
    size_t capacity() const;
    void clear();

    double& at(size_t i);
    double at(size_t i) const;

    void swap(vector &rhs);



private:
    std::unique_ptr<double[]> m_data;
    size_t m_capacity;
    size_t m_size;
};
