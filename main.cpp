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
    while (score < 1700000) {
        ofstream ofs("out");

        // Random solution
        map<set<int>, int> visited;

        ofs << C << "\n";
        srand(time(NULL) + score);
        for (int i = 0; i < C - 2; i++) {
            int a = 1000;
            int t = 0;
            int v = S;
            int oldV = v;
            vector<int> path{v};
            while (t < T - a) {
                if (oldV == 4389 && v == 7482) {
                    a = 100;
                }
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

        // 
        {
            int a = 1000;
            int t = 348;
            int v = 15;
            int oldV = v;
            vector<int> path{
                4516  ,
                7281  ,
                2751  ,
                2239  ,
                7075  ,
                8109  ,
                9480  ,
                9224  ,
                2890  ,
                4501  ,
                8399  ,
                8401  ,
                5819  ,
                9855  ,
                1786  ,
                4581  ,
                10057 ,
                2144  ,
                6125  ,
                3611  ,
                7610  ,
                5953  ,
                10241 ,
                7392  ,
                9074  ,
                155   ,
                3924  ,
                9098  ,
                1018  ,
                3295  ,
                3625  ,
                9124  ,
                5515  ,
                9544  ,
                4079  ,
                1359  ,
                8147  ,
                335   ,
                5141  ,
                1461  ,
                9210  ,
                10278 ,
                1906  ,
                15
            };
            visited[set<int>{4516    ,    7281    }] = 72;
            visited[set<int>{7281    ,    2751    }] = 10 ;
            visited[set<int>{2751    ,    2239    }] = 180;
            visited[set<int>{2239    ,    7075    }] = 82 ;
            visited[set<int>{7075    ,    8109    }] = 73 ;
            visited[set<int>{8109    ,    9480    }] = 44 ;
            visited[set<int>{9480    ,    9224    }] = 120;
            visited[set<int>{9224    ,    2890    }] = 133;
            visited[set<int>{2890    ,    4501    }] = 74 ;
            visited[set<int>{4501    ,    8399    }] = 96 ;
            visited[set<int>{8399    ,    8401    }] = 36 ;
            visited[set<int>{8401    ,    5819    }] = 178;
            visited[set<int>{5819    ,    9855    }] = 54 ;
            visited[set<int>{9855    ,    1786    }] = 37 ;
            visited[set<int>{1786    ,    4581    }] = 32 ;
            visited[set<int>{4581    ,    10057   }] = 3  ;
            visited[set<int>{10057   ,    2144    }] = 31 ;
            visited[set<int>{2144    ,    6125    }] = 77 ;
            visited[set<int>{6125    ,    3611    }] = 50 ;
            visited[set<int>{3611    ,    7610    }] = 174;
            visited[set<int>{7610    ,    5953    }] = 80 ;
            visited[set<int>{5953    ,    10241   }] = 220;
            visited[set<int>{10241   ,    7392    }] = 23 ;
            visited[set<int>{7392    ,    9074    }] = 83 ;
            visited[set<int>{9074    ,    155     }] = 13 ;
            visited[set<int>{155     ,    3924    }] = 119;
            visited[set<int>{3924    ,    9098    }] = 57 ;
            visited[set<int>{9098    ,    1018    }] = 62 ;
            visited[set<int>{1018    ,    3295    }] = 44 ;
            visited[set<int>{3295    ,    3625    }] = 195;
            visited[set<int>{3625    ,    9124    }] = 15 ;
            visited[set<int>{9124    ,    5515    }] = 84 ;
            visited[set<int>{5515    ,    9544    }] = 74 ;
            visited[set<int>{9544    ,    4079    }] = 73 ;
            visited[set<int>{4079    ,    1359    }] = 30 ;
            visited[set<int>{1359    ,    8147    }] = 6  ;
            visited[set<int>{8147    ,    335     }] = 88 ;
            visited[set<int>{335     ,    5141    }] = 68 ;
            visited[set<int>{5141    ,    1461    }] = 60 ;
            visited[set<int>{1461    ,    9210    }] = 65 ;
            visited[set<int>{9210    ,    10278   }] = 194;
            visited[set<int>{10278   ,    1906    }] = 258;
            visited[set<int>{1906    ,    15      }] = 203;
            while (t < T - a) {
                if (oldV == 4389 && v == 7482) {
                    a = 100;
                }
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

        // 2
        {
            int a = 1000;
            int t = 399;
            int v = 42;
            int oldV = v;
            vector<int> path{
4516, 
7281, 
2751, 
2239, 
7075, 
8109, 
9480, 
9224, 
2890, 
4501, 
8399, 
8401, 
5819, 
9855, 
1786, 
4581, 
10057, 
2144, 
6125, 
3611, 
7610, 
5953, 
10241, 
7392, 
9074, 
155, 
3924, 
9098, 
1018, 
3295, 
3625, 
9124, 
5515, 
378, 
3839, 
6126, 
430, 
7481, 
9578, 
4988, 
6899, 
2049, 
1658, 
2483, 
9522, 
876, 
8780, 
2700, 
10336, 
7727, 
2359, 
1555, 
42
            };
            visited[set<int>{4516,           7281,      }] = 72;
            visited[set<int>{7281,           2751,      }] = 10 ;
            visited[set<int>{2751,           2239,      }] = 180;
            visited[set<int>{2239,           7075,      }] = 82 ;
            visited[set<int>{7075,           8109,      }] = 73 ;
            visited[set<int>{8109,           9480,      }] = 44 ;
            visited[set<int>{9480,           9224,      }] = 120;
            visited[set<int>{9224,           2890,      }] = 133;
            visited[set<int>{2890,           4501,      }] = 74 ;
            visited[set<int>{4501,           8399,      }] = 96 ;
            visited[set<int>{8399,           8401,      }] = 36 ;
            visited[set<int>{8401,           5819,      }] = 178;
            visited[set<int>{5819,           9855,      }] = 54 ;
            visited[set<int>{9855,           1786,      }] = 37 ;
            visited[set<int>{1786,           4581,      }] = 32 ;
            visited[set<int>{4581,           10057,     }] = 3  ;
            visited[set<int>{10057,          2144,      }] = 31 ;
            visited[set<int>{2144,           6125,      }] = 77 ;
            visited[set<int>{6125,           3611,      }] = 50 ;
            visited[set<int>{3611,           7610,      }] = 174;
            visited[set<int>{7610,           5953,      }] = 80 ;
            visited[set<int>{5953,           10241,     }] = 220;
            visited[set<int>{10241,          7392,      }] = 23 ;
            visited[set<int>{7392,           9074,      }] = 83 ;
            visited[set<int>{9074,           155,       }] = 13 ;
            visited[set<int>{155,            3924,      }] = 119;
            visited[set<int>{3924,           9098,      }] = 57 ;
            visited[set<int>{9098,           1018,      }] = 62 ;
            visited[set<int>{1018,           3295,      }] = 44 ;
            visited[set<int>{3295,           3625,      }] = 195;
            visited[set<int>{3625,           9124,      }] = 15 ;
            visited[set<int>{9124,           5515,      }] = 84 ;
            visited[set<int>{5515,           378,       }] = 120;
            visited[set<int>{378,            3839,      }] = 21 ;
            visited[set<int>{3839,           6126,      }] = 19 ;
            visited[set<int>{6126,           430,       }] = 173;
            visited[set<int>{430,            7481,      }] = 149;
            visited[set<int>{7481,           9578,      }] = 78 ;
            visited[set<int>{9578,           4988,      }] = 59 ;
            visited[set<int>{4988,           6899,      }] = 64 ;
            visited[set<int>{6899,           2049,      }] = 114;
            visited[set<int>{2049,           1658,      }] = 92 ;
            visited[set<int>{1658,           2483,      }] = 85 ;
            visited[set<int>{2483,           9522,      }] = 114;
            visited[set<int>{9522,           876,       }] = 276;
            visited[set<int>{876,            8780,      }] = 143;
            visited[set<int>{8780,           2700,      }] = 69 ;
            visited[set<int>{2700,           10336,     }] = 15 ;
            visited[set<int>{10336,          7727,      }] = 94 ;
            visited[set<int>{7727,           2359,      }] = 8  ;
            visited[set<int>{2359,           1555,      }] = 96 ;
            visited[set<int>{1555,                  42  }] = 23 ;

            while (t < T - a) {
                if (oldV == 4389 && v == 7482) {
                    a = 100;
                }
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
