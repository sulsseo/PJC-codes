/**
 *  Created by Jakub Trmal on 03/01/2018.
 *
 *  Class is connected graph with rate edges
 *
 *  Support:
 *      Find closest path from node to node
 *
 */

#ifndef SEMESTRAL_GRAPH_HPP
#define SEMESTRAL_GRAPH_HPP

#include <iostream>
#include <map>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;

class graph {
private:

    // basic graph node implementation
    class node {
    public:
        node() = default;

        ~node() = default;

        node(unsigned int id) : m_id(id) {}

        const unsigned int get_id() const {
            return m_id;
        }

        double get_distance_to() const {
            return m_distance;
        }

        void set_distance(unsigned long distance) {
            node::m_distance = distance;
        }

        void set_id(unsigned int id) {
            node::m_id = id;
        }

        bool empty() {
            return m_id == 0;
        }

        friend ostream &operator<<(ostream &os, const node &obj) {
            os << "id: " << obj.get_id();
            os << ", dist: " << obj.get_distance_to();
            return os;
        }

        unsigned int m_id = 0;
        double m_distance = numeric_limits<double>::infinity();
    };

    class edge {
    public:
        edge(node *from, node *to, unsigned long cost) :
                m_from(from),
                m_to(to),
                m_cost(cost) {}

        ~edge() = default;

        const node *get_from() const {
            return m_from;
        }

        const node *get_to() const {
            return m_to;
        }

        const unsigned long get_cost() const {
            return m_cost;
        }

        friend ostream &operator<<(ostream &os, const edge &obj) {
            os << "[" << obj.get_from()->get_id() << "]";
            os << " -- " << obj.get_cost() << " -- ";
            os << "[" << obj.get_to()->get_id() << "]";
            return os;
        }

        const node *m_from;
        const node *m_to;
        const unsigned long m_cost;
    };

    size_t m_nodes{};
    size_t m_edges{};

    std::map<unsigned int, node> node_by_id;
    std::map<unsigned int, std::vector<edge>> outcoming_edges;

    void add_data(unsigned int from, unsigned int to, unsigned long cost) {
        node *n_from;
        node *n_to;

        if (node_by_id[from].empty()) {
            node_by_id[from].set_id(from);
        }

        if (node_by_id[to].empty()) {
            node_by_id[to].set_id(to);
        }

        n_from = &node_by_id[from];
        n_to = &node_by_id[to];

        outcoming_edges[from].emplace_back(n_from, n_to, cost);
        outcoming_edges[to].emplace_back(n_to, n_from, cost);
    }

public:

    graph() = default;

    ~graph() = default;

    /**
     *
     * @param nodes
     * @param edges
     */
    graph(size_t nodes, size_t edges) :
            m_nodes(nodes),
            m_edges(edges) {
    }


    /**
     * load data file from @param path in nnc format:
     *
     * nnc format in documentation
     *
     * @param path file path
     */
    void load_nnc_graph(std::string path);

    /**
     * Basic printer
     */
    void print_nodes();

    void print_edges();

    std::vector<unsigned long> compute_closest_path(unsigned int origin) {
        std::vector<unsigned long> result(m_nodes);

        // TODO dijkstra

        return result;
    }
};

#endif //SEMESTRAL_GRAPH_HPP
