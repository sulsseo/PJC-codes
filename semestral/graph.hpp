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
    size_t m_nodes;
    size_t m_edges;
//    int **data;
    std::map<int,std::map<int,int>> data;

    int minDistance(int dist[], bool visited[]) {
        int min = INT_MAX, min_index;

        for (int v = 0; v < m_nodes; v++)
            if (!visited[v] && dist[v] <= min)
                min = dist[v], min_index = v;

        return min_index;
    }

public:

    graph(std::string path) {
        load_nnc(path);
    }

    ~graph() = default;

    /**
     * load data file from @param path in nnc format:
     *
     * nnc format in documentation
     *
     * @param path file path
     */
    void load_nnc(std::string path);


    void print_solution(int *dist) {
        printf("Vertex   Distance from Source\n");
        for (int i = 0; i < m_nodes; i++)
            printf("%d \t\t %d\n", i + 1, dist[i]);
    }

    void print_matrix() {
        for (size_t i = 0; i < m_nodes; ++i) {
            for (size_t j = 0; j < m_nodes; ++j) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    /**
     * inspired by GeeksForGeeks
     *
     * @param src
     */
    void dijkstra(int src, int *dist) {
        bool visited[m_nodes];

        for (int i = 0; i < m_nodes; ++i)
            dist[i] = INT_MAX, visited[i] = false;

        dist[src] = 0;

        int idx = 0;
        while (idx < m_nodes-1) {

            // find closest neighbour
            int min = INT_MAX;
            int index = 0;
            for (int v = 0; v < m_nodes; ++v)
                if (!visited[v] && dist[v] <= min)
                    min = dist[v], index = v;

            visited[index] = true;

            for (int v = 0; v < m_nodes; ++v) {
                if (!visited[v] &&
                    data[index][v] != 0 &&
                    dist[index] != INT_MAX &&
                    dist[index] + data[index][v] < dist[v]) {
                    dist[v] = dist[index] + data[index][v];
                }
            }

            ++idx;
        }

//        print_solution(dist, m_nodes);
//        return dist;
    }

    size_t get_nodes() const;

    size_t get_edges() const;
};

#endif //SEMESTRAL_GRAPH_HPP
