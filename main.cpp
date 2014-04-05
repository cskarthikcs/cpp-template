// Chose which lib to use:
#define BOOST 0
#define SCC 1

#define LIB BOOST
//#define LIB SCC

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
#include <cstdio>

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

typedef vector<bool> line_t;
typedef vector<line_t> image_t;

template <class K, class V>
std::string map_to_str(std::map<K,V> map) {
    std::stringstream result;
    for (auto& pair : map) {
        result << pair.first << ":" << pair.second << ", ";
    }
    return result.str();
}

int count(int h, int w, int S, image_t &M){
    int count = 0;
    for(int i = h - S; i <= h + S; i++){
        for(int j = w - S; j <= w + S; j++){
            //printf("i j %d %d\n", i, j); cout.flush();
            if(M[i][j]){
                count++;
            }
        }
    }
    return count;
}

// To, Cost, length
typedef vector<int> edge_t;
typedef vector<vector<edge_t>> graph_t;

void print_graph(graph_t graph) {
    printf("A B D C L\n");
    for(int i = 0; i < graph.size(); ++i) {
        for(auto& edge : graph[i]) {
            printf("%d %d %d %d\n", i, edge[0], edge[1], edge[2]);
        }
    }
}

int main(int argc, char** argv) {

    ifstream ifs("input/street.txt");
    //ifstream ifs("input/street_min.txt");
    string trash;
    int N, M, T, C, S, buf;
    graph_t graph;

    ifs >> N;
    ifs >> M;
    ifs >> T;
    ifs >> C;
    ifs >> S;
    getline(ifs, trash);
    printf("N M T C S\n%d %d %d %d %d\n\n", N, M, T, C, S);

    // Latitudes
    for (int i = 0; i < N; ++i) {
        getline(ifs, trash);
    }

    // Edge params
    //printf("A B D C L\n");
    graph = graph_t(N);
    for (int i = 0; i < M; ++i) {
        int A, B, D, C, L;
        ifs >> A;
        ifs >> B;
        ifs >> D;
        ifs >> C;
        ifs >> L;
        getline(ifs, trash);
        graph[A].push_back(edge_t{B, C, L});
        if (D == 2) {
            graph[B].push_back(edge_t{A, C, L});
        }
        //printf("%d %d %d %d %d\n", A, B, D, C, L);
    }

    int score = 0;
    while (score < 1500000) {
        ofstream ofs("out");

        // Random solution
        map<set<int>, int> visited;

        ofs << C << "\n";
        srand(time(NULL) + score);
        for (int i = 0; i < C; i++) {
            int t = 0;
            int v = S;
            int oldV = v;
            vector<int> path{v};
            while (t < T - 500) {
                int d = graph[v].size();
                int choice = ((rand() % d) + d) % d;
                if (visited.find(set<int>{v,graph[v][choice][0]}) != visited.end()) {
                    choice = ((rand() % d) + d) % d;
                }
                t += graph[v][choice][1];
                oldV = v;
                v = graph[v][choice][0];
                path.push_back(v);
                visited[set<int>{oldV, v}] = graph[oldV][choice][2];
            }
            ofs << path.size() << "\n";
            for (auto& v : path) {
                ofs << v << "\n";
            }
        }
        score = 0;
        for (auto& pair : visited) {
            score += pair.second;
        }
        cout << "score " << score << endl;
    }

    //typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> graph_t;
    //typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_descriptor;
    //typedef boost::graph_traits<graph_t>::edge_descriptor edge_descriptor;
    //typedef std::pair<int, int> Edge;

    // Model inputs.
    //const int num_nodes = 5;
    //Edge edge_array[] = {
        //{0, 2}, {1, 1}, {1, 3}, {1, 4}, {2, 1},
        //{2, 3}, {3, 4}, {4, 0}, {4, 1}
    //};
    //int weights[] = {
        //1, 2, 1, 2, 7,
        //3, 1, 1, 1
    //};
    //print_graph(graph);
}
