//
// Created by ctsnz0060 on 24.07.2018.
//

#ifndef ULLMANNS_ALGORITHM_VERTICE_HPP
#define ULLMANNS_ALGORITHM_VERTICE_HPP

#include <vector>

class Vertice{
private:
    int m_id;
    int m_degree;
    std::vector<const Vertice*> m_adjacencyList;

public:
    explicit Vertice(int id): m_id(id) { m_degree = 0; };
    void addNeigborhood(const Vertice&);
    int getId(void);
};


#endif //ULLMANNS_ALGORITHM_VERTICE_HPP
