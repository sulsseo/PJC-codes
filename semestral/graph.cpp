//
// Created by Jakub Trmal on 03/01/2018.
//
#include "graph.hpp"

using namespace std;

void graph::load_nnc_graph(std::string path) {

    ifstream file(path);

    file >> this->m_nodes;
    file >> this->m_edges;

    unsigned int from;
    unsigned int to;
    unsigned long cost;

    for (size_t i = 0; i < this->m_edges; ++i) {
        file >> from;
        file >> to;
        file >> cost;
        add_data(from, to, cost);
    }
}

void graph::print_nodes() {
    for (auto it = node_by_id.begin(); it != node_by_id.end(); ++it) {
        cout << it.operator*().second << endl;
    }
}

void graph::print_edges() {
    auto it = outcoming_edges.begin().operator*().second.begin();
    cout << it.operator*() << endl;
}
