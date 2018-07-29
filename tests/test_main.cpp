//
// Created by ctsnz0060 on 29.07.2018.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <map>

#define MAX_NODE_SIZE 6;
int g_MAX_EDGE_SIZE = 10;
#define BIG_MAX_NODE_SIZE 20;
int g_BIG_MAX_EDGE_SIZE = 30;

int main()
{
    /* initialize random seed: */
    srand(time(NULL));

    int node_size = MAX_NODE_SIZE;
    int attribute_size = 2;
    int second_node_size = BIG_MAX_NODE_SIZE;

    std::map<int, std::vector<int>> first_graph;
    std::map<int, std::vector<int>> second_graph;

    for (int i = 0; i< node_size; i++){
        std::pair<int, std::vector<int>> temp_pair;
        temp_pair.first = i;
        temp_pair.second = std::vector<int>(0);
        first_graph.insert(temp_pair);
    }


    std::ofstream out("../../data/generated_1");
    if (out.is_open())
    {
        out << node_size << " " << attribute_size << std::endl;
    }

    for (int i = 0; i < g_MAX_EDGE_SIZE; i++){
        int r1, r2;
        bool check = true;
        do{
            r1 = std::rand() % MAX_NODE_SIZE;
            r2 = std::rand() % MAX_NODE_SIZE;

            if (std::find(std::begin(first_graph.at(r1)), std::end(first_graph.at(r1)), r2) == std::end(first_graph.at(r1))
                && std::find(std::begin(first_graph.at(r2)), std::end(first_graph.at(r2)), r1) == std::end(first_graph.at(r2))
                && r1 != r2)
            {
                check = false;
                first_graph.at(r1).push_back(r2);
            }
        } while (r1 == r2 || check);
    }

    for (auto i: first_graph){
        int node = i.first;
        for (auto j: i.second){
            out << node << " " << j << std::endl;
        }
    }

    out.close();

    out.open("../../data/generated_2");
    if(out.is_open())
    {
        out << second_node_size << " " << attribute_size << std::endl;
    }


    for (int i = 0; i< second_node_size; i++){
        std::pair<int, std::vector<int>> temp_pair;
        temp_pair.first = i;
        temp_pair.second = std::vector<int>(0);
        second_graph.insert(temp_pair);
    }

    for(auto &i: first_graph){
        second_graph.find(i.first)->second = i.second;
    }

    for (int i = 0; i < g_BIG_MAX_EDGE_SIZE; i++){
        int r1, r2;
        bool check = true;
        do{
            r1 = std::rand() % BIG_MAX_NODE_SIZE;
            r2 = std::rand() % BIG_MAX_NODE_SIZE;

            if (std::find(std::begin(second_graph.at(r1)), std::end(second_graph.at(r1)), r2) == std::end(second_graph.at(r1))
                && std::find(std::begin(second_graph.at(r2)), std::end(second_graph.at(r2)), r1) == std::end(second_graph.at(r2))
                && r1 != r2)
            {
                check = false;
                second_graph.at(r1).push_back(r2);
            }
        } while (r1 == r2 || check);
    }

    for (auto i: second_graph){
        int node = i.first;
        for (auto j: i.second){
            out << node << " " << j << std::endl;
        }
    }

    out.close();

    return 0;
}