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
int func(graph_t& graph,int v,int choice, vector<int>& ratio) {
//	cout<<"Yes"<<endl;	
	//double frac = 10*graph[v][choice][2]/graph[v][choice][1];
	double val= (pow(4,graph[graph[v][choice][0]].size() - ratio[graph[v][choice][0]]))*pow(graph[v][choice][2]/graph[v][choice][1], 1.1);
	//cout<<"No"<<endl;	
	int prod = 1;
    int u = graph[v][choice][0];
	for (int i = 0; i < graph[u].size(); ++i) {
	    if (graph[u][i][0] == v)
	        continue;
	    prod *= pow(3, graph[graph[u][i][0]].size() - ratio[graph[u][i][0]]) * (graph[u][i][2] / graph[u][i][1]);
	}
	return (int) val * prod;
    //return pow(2,25 - (double)graph[v][choice][1]/40)*(1-ratio[graph[v][choice][0]]);
}

void getratio(graph_t& graph, map<set<int>, int>& visited, vector<int>& output) {
    for(int i = 0; i < graph.size(); ++i) {
        int visited_count = 0;
        for(auto& edge : graph[i]) {
            if(visited.find(set<int>{i, edge[0]}) != visited.end()) {
                visited_count++;
            }
        }
//	cout<<"Yes"<<endl;	
        output.push_back(visited_count);
//	cout<<"No"<<endl;	
    }//Normal(output);
}

int main(int argc, char** argv) {
	int smart=0, dumb=0;
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
    while (score < 1420000) {
        ofstream ofs("out");
	vector<int> ratio(graph.size());
        // Random solution
        map<set<int>, int> visited;

        ofs << C << "\n";
        srand(time(NULL) + score);
//cout<<func(graph,0,0);
//cout<<"hi"<<endl;
//goes to 46

        for (int i = 0; i < C; ++i)
        {
            int a = 1000;
            int t = 0;
            int v = 4516;
            int oldV = v;
            vector<int> path{};
            getratio(graph,visited,ratio);

            while (t < T - a) {
                if (oldV == 4389 && v == 7482) {
                    a = 100;
                }
                int d = graph[v].size();

                vector<int> bias(d);
                int sum=0;

                for(int i = 0; i < d; ++i) {
                    bias[i]=func(graph,v,i,ratio);
                    sum += bias[i];
                }//cout<<"sum = "<<sum<<endl;

                int rv = (rand() % sum);
                sum = 0;

                int choice = d - 1;//bool working=false;
                for (int i = 0; i < d; ++i) {
                    sum += bias[i];
                    if (rv <= sum) {smart++;
                        choice = i;//cout<<"Yes";
			//working=true;
                        break;
                    }
                }//if(working==false){cout<<endl<<rv<<" "<<sum<<endl;exit(0);}

                    if (visited.find(set<int>{v,graph[v][choice][0]}) != visited.end() ) {
			if((rand()%5==0)){dumb++;
                        choice = ((rand() % d) + d) % d;//cout<<"No"<<endl;//}
		//	else cout<<"Neither"<<endl;
                    }}
		t += graph[v][choice][1];
                oldV = v;

                v = graph[v][choice][0];
                ratio[v]++;
		if(ratio[v]>graph[v].size())
			ratio[v]=graph[v].size();
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
        cout << "score " << score << "   "<<smart<<"/"<<dumb <<endl;smart=0;dumb=0;
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
