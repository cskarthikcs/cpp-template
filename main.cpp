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

int main(int argc, char** argv) {
    //ifstream ifs("input/doodle.txt");
    ifstream ifs("input/min.txt");
    ofstream ofs("out");
    int H, W;
    string line;
    ifs >> H;
    ifs >> W;
    getline(ifs, line);
    image_t M;
    vector<string> output;
    int h = 0;
    int w = 0;
    while(getline(ifs, line)){
        w = 0;
        line_t M_line;
        for (char &c : line) {
            if (c == '.') {
                M_line.push_back(false);
                cout << c;
            } else {
                M_line.push_back(true);
                cout << c;
                // Naive.
                //output.push_back(to_string(h) + " " + to_string(w));
            }
            w++;
        }
        M.push_back(M_line);
        h++;
        cout << "\n";
    }
    //ofs << output.size() << "\n";
    //for (auto &s : output){
        //ofs << "PAINTSQ " + s + " 0\n";
    //}

    int max_row_sum = 0, row_sum;
    for (auto &row : M) {
        row_sum = 0;
        for (auto c : row) {
            if (c) {
                row_sum++;
            }
        }
        if (row_sum > max_row_sum) {
            max_row_sum = row_sum;
        }
    }
    printf("max_row_sum %d\n", max_row_sum);

    float percent = 0.50f;
    int S = 1;
    int area = (2*S + 1) * (2*S + 1);
    h = S;
    w = S;
    cout << "W H " << W << " " << H << endl;
    for (int h = S; h < H - S; h++) {
        for (int w = S; w < W - S; w++) {
            printf("h w %d %d\n", h, w);
            int c = count(h, w, S, M);
            printf("count %d\n", c);
            if (c > area * percent) {
                output.push_back("PAINTQ " + to_string(h) + " " + to_string(w) + " " + to_string(S) + "\n");
                for(int i = h - S; i <= h + S; i++){
                    for(int j = w - S; j <= w + S; j++){
                        //printf("i j %d %d\n", i, j); cout.flush();
                        if(!M[i][j]){
                            output.push_back("ERASECELL " + to_string(i) + " " + to_string(j) + "\n");
                        }
                    }
                }
            }
        }
    }
    ofs << output.size() << "\n";
    for (auto &s : output) {
        ofs << s;
    }

    std::cout << "It works!" << std::endl;
}
