//
// Created by Jakub Trmal on 03/01/2018.
//
#include "graph.hpp"

using namespace std;

void graph::load_nnc(std::string path) {

    ifstream file;

    file.open(path);
    if (!file) {
        throw std::runtime_error("File not found!");
    }

    file >> this->m_nodes;
    file >> this->m_edges;

    // allocate data

    size_t from;
    size_t to;
    int cost;

    for (size_t i = 0; i < this->m_edges; ++i) {
        file >> from;
        file >> to;
        file >> cost;

        data[from - 1][to - 1] = cost;
        data[to - 1][from - 1] = cost;
    }
}

size_t graph::get_nodes() const {
    return m_nodes;
}

size_t graph::get_edges() const {
    return m_edges;
}


