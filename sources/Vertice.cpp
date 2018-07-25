//
// Created by ctsnz0060 on 24.07.2018.
//

#include "../headers/Vertice.hpp"

const int Vertice::getId(void) const
{
    return m_id;
}

const std::vector<Vertice*> Vertice::getNeigborhood() const
{
    return m_adjacencyList;
}

void Vertice::addNeigborhood(Vertice *node) {
    m_adjacencyList.push_back(node);
    m_degree++;
}

const int Vertice::getDegree(void) const {
    return m_degree;
}

bool Vertice::operator<(const Vertice &lhs, const Vertice &rhs) {
    return lhs.m_degree < rhs.m_degree;
}
