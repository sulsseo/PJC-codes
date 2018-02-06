#include "graph.hpp"

using namespace std;


graph::graph(std::string path) {
    load_nnc(path);
}

void graph::load_nnc(std::string path) {

    ifstream file;

    file.open(path);
    if (!file) {
        throw std::runtime_error("File not found!");
    }

    file >> this->m_nodes;
    file >> this->m_edges;


    size_t from, to;
    int cost;

    for (size_t i = 0; i < this->m_edges; ++i) {
        file >> from;
        file >> to;
        file >> cost;

        data[from - 1][to - 1] = cost;
        data[to - 1][from - 1] = cost;
    }
}

void graph::print_solution(std::mutex &mtx, int from, int *distance) {
    std::unique_lock<mutex> lock(mtx);

    cout << "------------------" << endl;
    cout << "From\tTo\tDistance" << endl;
    for (int i = 0; i < m_nodes; i++) {
        cout << from+1 << "\t\t" << i+1 << "\t\t" << distance[i] << endl;
    }
    cout << "------------------" << endl << endl;
}

void graph::print_matrix(std::mutex &mtx) {
    std::unique_lock<mutex> lock(mtx);
    for (size_t i = 0; i < m_nodes; ++i) {
        for (size_t j = 0; j < m_nodes; ++j) {
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void graph::dijkstra(int origin, int *distance) {
    bool visited[m_nodes];

    for (int i = 0; i < m_nodes; ++i)
        distance[i] = INT_MAX, visited[i] = false;

    distance[origin] = 0;

    int idx = 0;
    while (idx < m_nodes-1) {

        // find closest neighbour
        int bound = INT_MAX;
        int index = 0;
        for (int v = 0; v < m_nodes; ++v)
            if (!visited[v] && distance[v] <= bound)
                bound = distance[v], index = v;

        visited[index] = true;

        // update cost
        for (int v = 0; v < m_nodes; ++v) {
            if (distance[index] + data[index][v] < distance[v] &&
                !visited[v] &&
                data[index][v] != 0 &&
                distance[index] != INT_MAX) {
                distance[v] = distance[index] + data[index][v];
            }
        }

        ++idx;
    }
}

size_t graph::get_nodes() const {
    return m_nodes;
}

size_t graph::get_edges() const {
    return m_edges;
}

void graph::increase_matrix() {
    for (size_t i = 0; i < m_nodes; ++i) {
        for (size_t j = 0; j < m_nodes; ++j) {
            ++data[i][j];
        }
    }
}


