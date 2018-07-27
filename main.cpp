#include <iostream>
#include <fstream>
#include "headers/Graph.hpp"
#include "headers/GraphMaker.hpp"
#include "headers/Vertice.hpp"
#include <algorithm>
#include <map>


std::map<Vertice*, std::vector<Vertice*>> findCandidatesForSubGraph(Graph*, Graph*);

bool cmpVertice(const Vertice *s1, const Vertice *s2){
    return s1->getDegree() < s2->getDegree();
}

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

    auto cand_hashtable = findCandidatesForSubGraph(subGraph, graph);

    for (auto& el : cand_hashtable){
        std::cout << el.first->getId() << "-> ";

        for (auto& cand: el.second){
            std::cout << cand->getId() << " - ";
        }
        std::cout << "\n";
    }

    return 0;
}

std::map<Vertice*, std::vector<Vertice*>> findCandidatesForSubGraph(Graph* sub_graph, Graph* graph)
{
    std::map<Vertice*, std::vector<Vertice*>> candidate_hashtable;

    std::sort(std::begin(sub_graph->m_vertices), std::end(sub_graph->m_vertices), cmpVertice);
    std::sort(std::begin(graph->m_vertices), std::end(graph->m_vertices), cmpVertice);


    for(auto& vertice : sub_graph->m_vertices){
        std::pair<Vertice*, std::vector<Vertice*>> pair_candidate_ht;
        pair_candidate_ht.first = vertice;
        std::vector<Vertice*> candidate_vertices;
        for (auto& graph_vert: graph->m_vertices){
            if (graph_vert->getDegree() >= vertice->getDegree())
            {
                candidate_vertices.push_back(graph_vert);
            }
        }
        pair_candidate_ht.second = candidate_vertices;
        candidate_hashtable.insert(pair_candidate_ht);
    }

    return candidate_hashtable;

};
