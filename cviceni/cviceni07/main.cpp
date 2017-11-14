#include "vector.hpp"
#include <iostream>

void multiply_all(vector& v, double factor) {
    for (size_t i = 0; i < v.size(); i++) {
        v.at(i) *= factor;
    }
}

double accumulate(const vector& v) {
    double sum = 0;

    for (size_t i = 0; i < v.size(); i++) {
        sum += v.at(i);
    }

    return sum;
}

void print_vector(const vector& v) {
    std::cout << "capacity: " << v.capacity() << " size: " << v.size() << " data: ";

    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v.at(i) << ' ';
    }
    std::cout << '\n';
}

vector cat(vector v) {
    auto original_size = v.size();
    v.resize(v.size() * 2);
    for (size_t i = 0; i < original_size; ++i) {
        v.at(original_size + i) = v.at(i);
    }
    return v;
}

int main() {
    vector v1;
    v1.push_back(1.23);
    v1.push_back(2.34);
    vector v2 = v1;            // kopirujici konstruktor
    vector v3 = std::move(v2); // presunujici konstruktor
    vector v4 = cat(v3);       // kopirujici konstuktor a presunujici konstruktor

    std::cout << "v1: "; print_vector(v1);
    std::cout << "v2: "; print_vector(v2);
    std::cout << "v3: "; print_vector(v3);
    std::cout << "v4: "; print_vector(v4);

    vector v5;
    v5.push_back(1.23);
    v5.push_back(2.34);
    vector v6;
    v6 = v5;                   // kopirujici prirazeni
    vector v7;
    v7 = std::move(v6);        // presunujici prirazeni
    vector v8;
    v8 = cat(v7);              // kopirujici konstruktor a presunujici prirazeni

    std::cout << "v5: "; print_vector(v5);
    std::cout << "v6: "; print_vector(v6);
    std::cout << "v7: "; print_vector(v7);
    std::cout << "v8: "; print_vector(v8);
}
