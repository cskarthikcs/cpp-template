// Chose which lib to use:
#define BOOST 0
#define SCC 1

//#define LIB BOOST
#define LIB SCC

// stdlib headers

#include <algorithm>
#include <chrono>           //time operations
#include <exception>        //bad_alloc, bad_cast, bad_exception, bad_typeid, ios_base::failure
#include <fstream>          //ofstream, ifstream, fstream
#include <functional>       //bind2nd
#include <iostream>         //cout, endl
#include <iterator>         //iterator, iterator_traits, input_iterator_tag, advance, next
#include <list>             //list, forward_list
#include <limits>           //
#include <map>              //map, multimap
#include <memory>           //shared_ptr
#include <mutex>
#include <new>              //new
#include <numeric>          //partial sums, differences on std::vectors of numbers
#include <regex>
#include <set>              //set, multiset
#include <string>           //string
#include <sstream>          //stringstream
#include <thread>
#include <typeinfo>         //typeid, bad_typeid, bad_typecast
#include <typeindex>        //type_index
#include <tuple>            //tuple
#include <unordered_map>    //unordered_map, unordered_multimap
#include <utility>          //pair, forward, type_info, size_t
#include <vector>
#include <valarray>

// C headers:

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>

#if LIB == BOOST

// Boost 1.48
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_map/property_map.hpp>

#elif LIB == SCC
// Conflicts with boost Graph
#include "scc.hpp"
#endif

using namespace std;

template <class K, class V>
std::string map_to_str(std::map<K,V> map) {
    std::stringstream result;
    for (auto& pair : map) {
        result << pair.first << ":" << pair.second << ", ";
    }
    return result.str();
}

int main(int argc, char** argv) {

#if LIB == BOOST

    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> graph_t;
    typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_descriptor;
    typedef boost::graph_traits<graph_t>::edge_descriptor edge_descriptor;
    typedef std::pair<int, int> Edge;

    // Model inputs.
    const int num_nodes = 5;
    Edge edge_array[] = {
        {0, 2}, {1, 1}, {1, 3}, {1, 4}, {2, 1},
        {2, 3}, {3, 4}, {4, 0}, {4, 1}
    };
    int weights[] = {
        1, 2, 1, 2, 7,
        3, 1, 1, 1
    };

    // Solve
    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    graph_t g(edge_array, edge_array + num_arcs, weights, num_nodes);
    std::vector<vertex_descriptor> p(num_vertices(g));
    std::vector<int> d(num_vertices(g));
    vertex_descriptor s = vertex(0, g);
    dijkstra_shortest_paths(g, s,
        predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
        distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));

    // Print solution to stdout.
    std::cout <<"distances and parents:" <<std::endl;
    boost::graph_traits<graph_t>::vertex_iterator vi, vend;
    for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi) {
        std::cout << "distance(" << *vi << ") = " << d[*vi] << ", "
                    << "wparent("  << *vi << ") = " << p[*vi] << std::endl;
    }
    std::cout <<std::endl;

    // Generate a .dot graph file with shortest path highlighted.
    // To png with: dot -Tpng -o outfile.png input.dot
    boost::property_map<graph_t, boost::edge_weight_t>::type weightmap = get(boost::edge_weight, g);
    std::ofstream dot_file("dijkstra.dot");
    dot_file << "digraph D {\n"      << "  rankdir=LR\n"           << "  size=\"4,3\"\n"
                << "  ratio=\"fill\"\n" << "  edge[style=\"bold\"]\n" << "  node[shape=\"circle\"]\n";
    boost::graph_traits <graph_t>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
        edge_descriptor e = *ei;
        boost::graph_traits<graph_t>::vertex_descriptor
            u = source(e, g), v = target(e, g);
        dot_file << u << " -> " << v << "[label=\"" << get(weightmap, e) << "\"";
        if (p[v] == u)
            dot_file << ", color=\"black\"";
        else
            dot_file << ", color=\"grey\"";
        dot_file << "]";
    }
    dot_file << "}";

#elif LIB == SCC

    // Read graph from file
    const IndexType NodeNumber = 15 + 1; // 15 graph nodes + dummy 0 node
    Graph nodes(NodeNumber);
    std::cout << "reading graph" << std::endl;
    Scc::readGraphFromFile("input/scc", nodes);

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

    // Dijkstra graph
    Graph dijkstraGraph(NodeNumber);
    Dijkstra::readGraphFromFile("in/dijkstra",dijkstraGraph);
    //long path = Dijkstra::findShortestPath(dijkstraGraph, 1, 15);

    dijkstraGraph.resetSearchData();

    // Run DFS search
    dijkstraGraph.totalDFS();
#endif
    std::cout << "It works!" << std::endl;
}
