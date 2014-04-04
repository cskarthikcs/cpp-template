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

#elif LIB == SCC
    // Read graph from file
    const IndexType NodeNumber = 15 + 1;
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

#endif
    std::cout << "It works!" << std::endl;
}
