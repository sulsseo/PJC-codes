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
    size_t m_nodes{};
    size_t m_edges{};
    std::map<int,std::map<int,int>> data;

public:

    graph() = default;

    /**
     * Constructor which load data from given file
     *
     * @param path to file with graph data
     */
    explicit graph(std::string path);

    ~graph() = default;

    /**
     * load data file from @param path in nnc format:
     *
     * nnc format in documentation
     *
     * @param path file path
     */
    void load_nnc(std::string path);

    /**
     * Thread safe print solution of given data
     *
     * @param mtx locker instance
     * @param distance computed closest distances
     */
    void print_solution(std::mutex &mtx, int from, int *distance);

    /**
     * Control print
     */
    void print_matrix(std::mutex &mtx);

    /**
     * instantly increase matrix +1
     */
    void increase_matrix();

    /**
     * Dijkstra find closest path in rated graph
     * inspired by GeeksForGeeks
     *
     * @param origin origin node
     * @param distance storage to save results
     */
    void dijkstra(int origin, int *distance);

    /**
     * Getter for private variable contain number of nodes
     *
     * @return number of nodes
     */
    size_t get_nodes() const;

    /**
     * Getter for private variable contain number of edges
     *
     * @return number of edges
     */
    size_t get_edges() const;
};

#endif //SEMESTRAL_GRAPH_HPP
