#include <iostream>
#include <fstream>
#include "headers/Graph.hpp"
#include "headers/GraphMaker.hpp"
#include <algorithm>
#include <map>


std::map<Vertice*, std::vector<Vertice*>> findCandidatesForSubGraph(Graph*, Graph*);

int main() {
/*
    Graph* graph;
    size_t nodeNumber;
    std::ifstream in("../data/graph1.txt");

    in >> nodeNumber;
    if (!in.fail())
    {
        graph = new Graph(nodeNumber, false);

        while(!in.eof())
        {
            int x1, x2;
            in >> x1;
            in >> x2;

            Vertice *to = graph->m_vertices.at(x1);
            Vertice *from = graph->m_vertices.at(x2);

            graph->AddEdge(to, from);
        }
    }
    else
    {
        std::cout << "node number read operation failed." << std::endl;
    }
*/

    Graph* subGraph = GraphMaker::CreateAGraph("../data/graph1.txt");

    Graph* graph = GraphMaker::CreateAGraph("../data/graph2.txt");

    std::sort(std::begin(graph->m_vertices), std::end(graph->m_vertices));
/*
    std::map<Vertice*, std::vector<Vertice*>> matrix;

    std::pair<Vertice*, std::vector<Vertice*>> firstPair;
    firstPair.first = new Vertice(3);
    firstPair.second = std::vector(5, new Vertice(2));

    matrix.insert(firstPair);
*/

    for (auto& el : graph->m_vertices){ //why auto&

        std::cout << el->getId() << "(Degree: " << el->getDegree() << ")" << std::endl;

        for (auto& neigh: el->getNeigborhood())
        {
            std::cout << neigh->getId() << ", ";
        }
        std::cout << '\n';
    }

    return 0;
}

std::map<Vertice*, std::vector<Vertice*>> findCandidatesForSubGraph(Graph*, Graph*)
{

};