//
// Created by ctsnz0060 on 24.07.2018.
//

#ifndef ULLMANNS_ALGORITHM_GRAPH_HPP
#define ULLMANNS_ALGORITHM_GRAPH_HPP

#include <vector>
#include "Vertice.hpp"

class Graph {
public:
    std::vector<const Vertice*> m_vertices;
    Graph(size_t numberOfNodes): m_numberOfNodes(numberOfNodes)
    {
        m_vertices.resize(m_numberOfNodes);
    };



private:
    size_t  m_numberOfNodes;

};


#endif //ULLMANNS_ALGORITHM_GRAPH_HPP
