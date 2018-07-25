//
// Created by ctsnz0060 on 24.07.2018.
//

#ifndef ULLMANNS_ALGORITHM_GRAPH_HPP
#define ULLMANNS_ALGORITHM_GRAPH_HPP

#include <vector>
#include "Vertice.hpp"

class Graph {
private:
    bool m_isDirected = false; //false for a bidirected graph, true for a directed graph.

public:
    std::vector<Vertice*> m_vertices;

    //constructors:
    Graph(size_t numberOfNodes): m_numberOfNodes(numberOfNodes)
    {
        InitializeVerticeVector();
    };

    Graph(size_t numberOfNodes, bool isDirected): m_numberOfNodes(numberOfNodes), m_isDirected(isDirected)
    {
        InitializeVerticeVector();
    };

    void AddEdge(Vertice*, Vertice*);
    void SortVertices(void);
private:
    size_t  m_numberOfNodes;
    void InitializeVerticeVector();
};


#endif //ULLMANNS_ALGORITHM_GRAPH_HPP
