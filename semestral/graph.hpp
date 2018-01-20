//
// Created by Jakub Trmal on 03/01/2018.
//

#ifndef SEMESTRAL_GRAPH_HPP
#define SEMESTRAL_GRAPH_HPP

#include <iostream>
#include <map>

struct node {
    unsigned long id;
    size_t num_of_edges;
};

struct edge {
    unsigned int cost;
    node from;
    node to;
};

class graph {
    
    
    std::map<unsigned long, node> node_by_id;
    std::map<unsigned long, std::vector<edge>> outcoming_edges;


    size_t vertices;
    size_t edges;
    
//    std::map<i
};


#endif //SEMESTRAL_GRAPH_HPP
