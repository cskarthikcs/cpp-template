#include <cassert>
#include <iostream>

#include "scc.hpp"

int i = 0;
int main(int argc, char** argv) {
    //#scc
    {
        // Read graph from file
        const IndexType NodeNumber = 15 + 1;
        Graph nodes(NodeNumber);
        std::cout << "reading graph" << std::endl;
        Scc::readGraphFromFile("scc.in", nodes);

        // Run BFS search
        nodes.totalBFS();

        nodes.resetSearchData();


        // Run search of Strongly connected components
        Scc::initIndexMap(NodeNumber);
        Scc::Results results;
        results.reserve(1000);
        Scc::DFS(nodes, results, Backward);


        Scc::translateNodes(nodes);
        Scc::DFS(nodes,results, Forward);

        std::sort (results.begin(), results.end(), Scc::mySortPred);

        std::cout << "SCC results: ";
        for (IndexType i = 0; i < results.size(); i++)
            std::cout << results[i] << ",";
        std::cout << std::endl;
    }
    std::cout << "It works!" << std::endl;
}
