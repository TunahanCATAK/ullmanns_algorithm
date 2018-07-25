//
// Created by ctsnz0060 on 25.07.2018.
//

#include <fstream>
#include "../headers/GraphMaker.hpp"

Graph *GraphMaker::CreateAGraph(std::string path) {
    int nodeNumber;
    int attributeCountPerLine;
    std::ifstream in(path);
    Graph* graph = nullptr;

    in >> nodeNumber;
    in >> attributeCountPerLine;
    if (!in.fail())
    {
        graph = new Graph(nodeNumber, false);

        while(!in.eof())
        {
            std::vector<int> attributes;

            for (int i = 0; i < attributeCountPerLine; i++){
                int tempVar;
                in >> tempVar;

                attributes.push_back(tempVar);
            }

            Vertice *to = graph->m_vertices.at(attributes.at(0));
            Vertice *from = graph->m_vertices.at(attributes.at(1));

            graph->AddEdge(to, from);
        }
    }
    else
    {
//        std::cout << "node number read operation failed." << std::endl;
    }

    return graph;
}
