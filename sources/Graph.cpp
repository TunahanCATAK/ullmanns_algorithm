//
// Created by ctsnz0060 on 24.07.2018.
//

#include "../headers/Graph.hpp"
#include <algorithm>

void Graph::InitializeVerticeVector() {
    for(unsigned int i = 0; i < m_numberOfNodes; i++){
        Vertice* tempVertice = new Vertice(i);
        m_vertices.push_back(tempVertice);
    }
}

void Graph::AddEdge(Vertice *to, Vertice *from) {
    if (m_isDirected)
    {
        to->addNeigborhood(from);
    }
    else
    {
        to->addNeigborhood(from);
        from->addNeigborhood(to);
    }
}

void Graph::SortVertices(void) {
    std::sort(std::begin(m_vertices), std::end(m_vertices));
}

