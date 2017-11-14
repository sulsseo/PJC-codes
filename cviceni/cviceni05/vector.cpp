//
// Created by Jakub Trmal on 31.10.17.
//

#include <iostream>
#include "vector.hpp"

void vector::print() {
    if (m_size != 0) {
        int i = 0;
        while (i < m_size) {
            std::cout<<m_data[i];
            ++i;
        }
        std::cout<<std::endl;
    }
}

void vector::push_back() {
    if (m_capacity == 0) {
        m_data = new T_vectorData(INIT_CAPACITY);
    }
}

vector::vector() {

}
