#include <iostream>
#include <fstream>
#include "headers/Graph.hpp"
#include "headers/GraphMaker.hpp"
#include "headers/Vertice.hpp"
#include <algorithm>
#include <map>
#include <stack>


std::map<Vertice*, std::vector<Vertice*>> findCandidatesForSubGraph(Graph*, Graph*);
std::map<Vertice*, std::vector<Vertice*>> refineCandidateMatrix(std::map<Vertice*, std::vector<Vertice*>>*);
std::map<Vertice*, std::vector<Vertice*>> pickACandidate(Vertice*, Vertice*, std::map<Vertice*, std::vector<Vertice*>>*);
bool StopCheck(std::map<Vertice*, std::vector<Vertice*>>*);
int matchAndContinue(std::map<Vertice*, std::vector<Vertice*>>*, int, int);

bool cmpVertice(const Vertice *s1, const Vertice *s2){
    return s1->getDegree() < s2->getDegree();
}

std::vector<std::map<Vertice*, std::vector<Vertice*>>> matched_nodes;
std::stack<int> index_sub_graph_stack;
std::stack<int> index_graph_stack;
std::stack<std::map<Vertice*, std::vector<Vertice*>>*> candidate_ht_stack;

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
    }
*/

    cand_hashtable = refineCandidateMatrix(&cand_hashtable);


    //Debug Info:
    std::cout << "-------------After Refinement Process---------------" << std::endl;

    for (auto& el : cand_hashtable){
        std::cout << el.first->getId() << "-> ";

        for (auto& cand: el.second){
            std::cout << cand->getId() << " - ";
        }
        std::cout << "\n";
    }

    int result = matchAndContinue(&cand_hashtable, 0, 0);
/*        //Debug Info:
        std::cout << "-------------Matched Nodes---------------" << std::endl;

        for (auto& el : cand_hashtable){
            std::cout << el.first->getId() << "-> ";

            for (auto& cand: el.second){
                std::cout << cand->getId() << " - ";
            }
            std::cout << "\n";
        }*/

    if (matched_nodes.size() == 0){
        std::cout << "There is no isomorphism" << std::endl;
    }
    else{
        std::cout << "-------------------------------------------------" <<std::endl;
        std::cout << "-------------------------------------------------" <<std::endl;

        for (std::map<Vertice*, std::vector<Vertice*>> item: matched_nodes){
            for (auto &el : item){
                std::cout << el.first->getId() << "-> ";

                for (auto& cand: el.second){
                    std::cout << cand->getId() << " - ";
                }
                std::cout << "\n";
            }
            std::cout << "-----------------------------------" << std::endl;
        }

        std::cout << "-------------------------------------------------" <<std::endl;
        std::cout << "-------------------------------------------------" <<std::endl;
    }

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
    return new_candidate_ht;
}

int matchAndContinue(std::map<Vertice*, std::vector<Vertice*>> *candidate_ht, int index_sub_graph, int index_graph)
{
    std::map<Vertice*, std::vector<Vertice*>>::iterator it = candidate_ht->begin();

    for (int i = 0; i < index_sub_graph; i++){
        it++;
    }
    
    Vertice* sub_graph_vertice = it->first;
    std::vector<Vertice*> graph_vertices = it->second;
    
    if (graph_vertices.size() <= index_graph)
    {
        if (index_graph_stack.size() == 0)
            return -1;
        else{

            int i = index_sub_graph_stack.top();
            int j = index_graph_stack.top();
            std::map<Vertice *, std::vector<Vertice *>> *ht = static_cast<std::map<Vertice *, std::vector<Vertice *>> *>(candidate_ht_stack.top());
            //delete top elements:
            index_graph_stack.pop();
            index_sub_graph_stack.pop();
            candidate_ht_stack.pop();

/*            //Debug Info:
            std::cout << "-------------When Push Backed-1---------------" << std::endl;

            for (auto& el : *ht){
                std::cout << el.first->getId() << "-> ";

                for (auto& cand: el.second){
                    std::cout << cand->getId() << " - ";
                }
                std::cout << "\n";
            }*/

            return matchAndContinue(ht, i, j + 1);
        }
    }

    Vertice* graph_vertice = graph_vertices.at(index_graph);
    
    std::map<Vertice*, std::vector<Vertice*>> new_candidate_ht = pickACandidate(sub_graph_vertice, graph_vertice, candidate_ht);
    new_candidate_ht = refineCandidateMatrix(&new_candidate_ht);
    
    if (!StopCheck(&new_candidate_ht)){
//        std::cout << "Matched Node: " << sub_graph_vertice->getId() << " - " << graph_vertice->getId() << std::endl;
        index_graph_stack.push(index_graph);
        index_sub_graph_stack.push(index_sub_graph);
        candidate_ht_stack.push(candidate_ht);
/*

        //Debug Info:
        std::cout << "-------------Pushed Hash--------------" << std::endl;

        for (auto& el : *candidate_ht){
            std::cout << el.first->getId() << "-> ";

            for (auto& cand: el.second){
                std::cout << cand->getId() << " - ";
            }
            std::cout << "\n";
        }
        // Debug Info End.
*/

        if (index_sub_graph == candidate_ht->size() - 1){
            matched_nodes.push_back(new_candidate_ht);

            int i = index_sub_graph_stack.top();
            int j = index_graph_stack.top();
            std::map<Vertice *, std::vector<Vertice *>> *ht = static_cast<std::map<Vertice *, std::vector<Vertice *>> *>(candidate_ht_stack.top());
            //delete top elements:
            index_graph_stack.pop();
            index_sub_graph_stack.pop();
            candidate_ht_stack.pop();

/*
            //Debug Info:
            std::cout << "-------------When Push Backed---------------" << std::endl;

            for (auto& el : *ht){
                std::cout << el.first->getId() << "-> ";

                for (auto& cand: el.second){
                    std::cout << cand->getId() << " - ";
                }
                std::cout << "\n";
            }
*/

            return matchAndContinue(ht, i, j + 1);

        }

        return matchAndContinue(&new_candidate_ht, index_sub_graph + 1, 0);
    }
    else
    {
//        std::cout << "No match, " << index_sub_graph << " - " << index_graph << std::endl;
        return matchAndContinue(candidate_ht, index_sub_graph, index_graph + 1);
    }
    
}


std::map<Vertice*, std::vector<Vertice*>> pickACandidate(Vertice* sub_graph_vertice, Vertice* graph_vertice, std::map<Vertice*, std::vector<Vertice*>> *candidate_ht)
{
    std::map<Vertice*, std::vector<Vertice*>> new_candidate_ht = *candidate_ht;

    new_candidate_ht.find(sub_graph_vertice)->second = std::vector<Vertice*>(1, graph_vertice);
    for (auto& item: new_candidate_ht){
        if (item.first != sub_graph_vertice)
        {
            item.second.erase(std::remove(std::begin(item.second), std::end(item.second), graph_vertice),std::end(item.second));
        }
    }

/*
    //Debug Info:
    std::cout << "-------------After Delete Candidate Process In pickACandidate---------------" << std::endl;
    for (auto& el : new_candidate_ht){
        std::cout << el.first->getId() << "-> ";

        for (auto& cand: el.second){
            std::cout << cand->getId() << " - ";
        }
        std::cout << "\n";
    }
*/

    return new_candidate_ht;

};

bool StopCheck(std::map<Vertice*, std::vector<Vertice*>>* candidate_ht)
{
    for(auto& item: *candidate_ht){
        if (item.second.size() == 0)
            return true;
    }

    return false;
}