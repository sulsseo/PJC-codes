//
// Created by Jakub Trmal on 31.10.17.
//

#ifndef CVICENI05_VECTOR_H
#define CVICENI05_VECTOR_H


#include <cstddef>

typedef double T_vectorData;

class vector {
private:
    std::size_t m_capacity = 0;
    std::size_t m_size = 0;
    double* m_data = nullptr;

    static const std::size_t INIT_CAPACITY = 3;

public:
    // constructor
    vector();
    vector(std::size_t capacity);
    vector(const vector &v);

    // destructor
    ~vector();


    void print();
    void push_back();



};


#endif //CVICENI05_VECTOR_H
