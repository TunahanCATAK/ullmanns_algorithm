#include <iostream>
#include <fstream>
#include "headers/Graph.hpp"
#include <algorithm>

int main() {
    std::cout << "Hello, World!" << std::endl;

    Graph* graph;

    size_t nodeNumber = 4;

    std::ifstream in("../data/graph1.txt");
    in >> nodeNumber;
    if (!in.fail())
    {
        graph = new Graph(nodeNumber);

        while(!in.eof())
        {
            int x1, x2;
            in >> x1;
            in >> x2;

//            auto pos = std::find_if(graph->m_vertices.begin(), graph->m_vertices.end(), [](Vertice& elem){ return (elem.getId() == (size_t)x1); });
        }
    }
    else
    {
        std::cout << "node number read operation failed." << std::endl;
    }


    return 0;
}