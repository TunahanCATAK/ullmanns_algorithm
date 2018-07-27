#include <iostream>
#include <fstream>
#include "headers/Graph.hpp"
#include "headers/GraphMaker.hpp"
#include "headers/Vertice.hpp"
#include <algorithm>
#include <map>


std::map<Vertice*, std::vector<Vertice*>> findCandidatesForSubGraph(Graph*, Graph*);
std::map<Vertice*, std::vector<Vertice*>> refineCandidateMatrix(std::map<Vertice*, std::vector<Vertice*>>*);

bool cmpVertice(const Vertice *s1, const Vertice *s2){
    return s1->getDegree() < s2->getDegree();
}

int main(int args, char **argv) {

    if (args != 3){
        return -1;
    }

/*
 * //Debug Info:
    std::cout << argv[1] << std::endl;
    std::cout << argv[2] << std::endl;

*/

    Graph* subGraph = GraphMaker::CreateAGraph(argv[1]);

    Graph* graph = GraphMaker::CreateAGraph(argv[2]);

/*
    //Debug Infos:
    for (auto& el : graph->m_vertices){ //why auto&

        std::cout << el->getId() << "(Degree: " << el->getDegree() << ")" << std::endl;

        for (auto& neigh: el->getNeigborhood())
        {
            std::cout << neigh->getId() << ", ";
        }
        std::cout << '\n';
    }

 */
    auto cand_hashtable = findCandidatesForSubGraph(subGraph, graph);

/*
    //Debug Info:
    for (auto& el : cand_hashtable){
        std::cout << el.first->getId() << "-> ";

        for (auto& cand: el.second){
            std::cout << cand->getId() << " - ";
        }
        std::cout << "\n";
    }*/


    cand_hashtable = refineCandidateMatrix(&cand_hashtable);


/*    //Debug Info:
    std::cout << "-------------After Refinement Process---------------" << std::endl;

    for (auto& el : cand_hashtable){
        std::cout << el.first->getId() << "-> ";

        for (auto& cand: el.second){
            std::cout << cand->getId() << " - ";
        }
        std::cout << "\n";
    }*/



    return 0;
}

std::map<Vertice*, std::vector<Vertice*>> findCandidatesForSubGraph(Graph* sub_graph, Graph* graph)
{
    std::map<Vertice*, std::vector<Vertice*>> candidate_hashtable;

    std::sort(std::begin(sub_graph->m_vertices), std::end(sub_graph->m_vertices), cmpVertice); //todo: instead of lambda function, use operator< overloading.
    std::sort(std::begin(graph->m_vertices), std::end(graph->m_vertices), cmpVertice);


    for(auto& vertice : sub_graph->m_vertices){
        std::pair<Vertice*, std::vector<Vertice*>> pair_candidate_ht;
        //todo: use find_if with lambda expr. to find candidate nodes.
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

std::map<Vertice*, std::vector<Vertice*>> refineCandidateMatrix(std::map<Vertice*, std::vector<Vertice*>> *candidate_ht) {
    std::map<Vertice *, std::vector<Vertice *>> new_candidate_ht;

    for (auto &pair: *candidate_ht) {
        std::pair<Vertice *, std::vector<Vertice *>> pair_new_cand_ht;
        Vertice *sub_graph_vertice = pair.first;
        pair_new_cand_ht.first = sub_graph_vertice;
        std::vector<Vertice *> new_candidate_vertices;

        std::vector<Vertice *> neighborhood_sub_graph_vertice = sub_graph_vertice->getNeigborhood();

        for (auto &graph_vertice : pair.second) {
            std::vector<Vertice *> neighborhood_graph_vertice = graph_vertice->getNeigborhood();
            int match_count = 0;

            for (auto item: neighborhood_sub_graph_vertice) {
                bool check = false;
                for (auto item1 : neighborhood_graph_vertice) {
                    if (std::find(std::begin(candidate_ht->find(item)->second),
                                  std::end(candidate_ht->find(item)->second), item1) !=
                        std::end(candidate_ht->find(item)->second)) {
                        check = true;
                        match_count++;
                        break;
                    }
                }
                if (check == true) {
                    continue;
                }
            }

            if (match_count >= neighborhood_sub_graph_vertice.size()) {
                new_candidate_vertices.push_back(graph_vertice);
            }
        }

        pair_new_cand_ht.second = new_candidate_vertices;
        new_candidate_ht.insert(pair_new_cand_ht);
    }

/*

    std::cout << "-------------Inside Of Refinement Process---------------" << std::endl;
    //Debug Info:
    for (auto &el : new_candidate_ht) {
        std::cout << el.first->getId() << "-> ";

        for (auto &cand: el.second) {
            std::cout << cand->getId() << " - ";
        }
        std::cout << "\n";
    }
*/

    return new_candidate_ht;
}