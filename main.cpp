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
int func(graph_t& graph,int v,int choice, vector<int>& ratio){
//	cout<<"Yes"<<endl;	
	//double frac = 10*graph[v][choice][2]/graph[v][choice][1];
	double val= (pow(16,graph[graph[v][choice][0]].size() - ratio[graph[v][choice][0]]))*graph[v][choice][2]/graph[v][choice][1];
	//cout<<"No"<<endl;	
	return (int) val;
//	return pow(2,25 - (double)graph[v][choice][1]/40)*(1-ratio[graph[v][choice][0]]);
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
    while (score < 1500000) {
        ofstream ofs("out");
	vector<int> ratio(graph.size());
        // Random solution
        map<set<int>, int> visited;

        ofs << C << "\n";
        srand(time(NULL) + score);
//cout<<func(graph,0,0);
//cout<<"hi"<<endl;
//goes to 46

{
            int a = 1000;
            int t = 900;
            int v = 46;
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
9544, 
4079, 
1359, 
8147, 
335, 
1403, 
9716, 
3230, 
8455, 
8017, 
5986, 
538, 
3315, 
5594, 
10038, 
7421, 
4768, 
6944, 
5109, 
1415, 
8392, 
477, 
2254, 
1116, 
401, 
2922, 
4335, 
9106, 
9432, 
1850, 
1397, 
1654, 
1866, 
4712, 
4583, 
7380, 
9909, 
11264, 
4718, 
2531, 
1795, 
354, 
7249, 
6298, 
5950, 
1757, 
9343, 
3726, 
1316, 
5463, 
2204, 
9123, 
149, 
3043, 
8258, 
10469, 
1787, 
256, 
2724, 
46

            };
visited[set<int>{4516,7281}]=72;
visited[set<int>{7281,2751}]=10;
visited[set<int>{2751,2239}]=180;
visited[set<int>{2239,7075}]=82;
visited[set<int>{7075,8109}]=73;
visited[set<int>{8109,9480}]=44;
visited[set<int>{9480,9224}]=120;
visited[set<int>{9224,2890}]=133;
visited[set<int>{2890,4501}]=74;
visited[set<int>{4501,8399}]=96;
visited[set<int>{8399,8401}]=36;
visited[set<int>{8401,5819}]=178;
visited[set<int>{5819,9855}]=54;
visited[set<int>{9855,1786}]=37;
visited[set<int>{1786,4581}]=32;
visited[set<int>{4581,10057}]=3;
visited[set<int>{10057,2144}]=31;
visited[set<int>{2144,6125}]=77;
visited[set<int>{6125,3611}]=50;
visited[set<int>{3611,7610}]=174;
visited[set<int>{7610,5953}]=80;
visited[set<int>{5953,10241}]=220;
visited[set<int>{10241,7392}]=23;
visited[set<int>{7392,9074}]=83;
visited[set<int>{9074,155}]=13;
visited[set<int>{155,3924}]=119;
visited[set<int>{3924,9098}]=57;
visited[set<int>{9098,1018}]=62;
visited[set<int>{1018,3295}]=44;
visited[set<int>{3295,3625}]=195;
visited[set<int>{3625,9124}]=15;
visited[set<int>{9124,5515}]=84;
visited[set<int>{5515,9544}]=74;
visited[set<int>{9544,4079}]=73;
visited[set<int>{4079,1359}]=30;
visited[set<int>{1359,8147}]=6;
visited[set<int>{8147,335}]=88;
visited[set<int>{335,1403}]=338;
visited[set<int>{1403,9716}]=192;
visited[set<int>{9716,3230}]=122;
visited[set<int>{3230,8455}]=127;
visited[set<int>{8455,8017}]=81;
visited[set<int>{8017,5986}]=137;
visited[set<int>{5986,538}]=32;
visited[set<int>{538,3315}]=166;
visited[set<int>{3315,5594}]=244;
visited[set<int>{5594,10038}]=75;
visited[set<int>{10038,7421}]=65;
visited[set<int>{7421,4768}]=54;
visited[set<int>{4768,6944}]=50;
visited[set<int>{6944,5109}]=93;
visited[set<int>{5109,1415}]=23;
visited[set<int>{1415,8392}]=87;
visited[set<int>{8392,477}]=161;
visited[set<int>{477,2254}]=285;
visited[set<int>{2254,1116}]=79;
visited[set<int>{1116,401}]=126;
visited[set<int>{401,2922}]=53;
visited[set<int>{2922,4335}]=59;
visited[set<int>{4335,9106}]=80;
visited[set<int>{9106,9432}]=18;
visited[set<int>{9432,1850}]=33;
visited[set<int>{1850,1397}]=22;
visited[set<int>{1397,1654}]=32;
visited[set<int>{1654,1866}]=72;
visited[set<int>{1866,4712}]=315;
visited[set<int>{4712,4583}]=126;
visited[set<int>{4583,7380}]=179;
visited[set<int>{7380,9909}]=71;
visited[set<int>{9909,11264}]=14;
visited[set<int>{11264,4718}]=92;
visited[set<int>{4718,2531}]=132;
visited[set<int>{2531,1795}]=142;
visited[set<int>{1795,354}]=70;
visited[set<int>{354,7249}]=96;
visited[set<int>{7249,6298}]=7;
visited[set<int>{6298,5950}]=203;
visited[set<int>{5950,1757}]=54;
visited[set<int>{1757,9343}]=67;
visited[set<int>{9343,3726}]=129;
visited[set<int>{3726,1316}]=168;
visited[set<int>{1316,5463}]=132;
visited[set<int>{5463,2204}]=138;
visited[set<int>{2204,9123}]=233;
visited[set<int>{9123,149}]=38;
visited[set<int>{149,3043}]=163;
visited[set<int>{3043,8258}]=65;
visited[set<int>{8258,10469}]=31;
visited[set<int>{10469,1787}]=37;
visited[set<int>{1787,256}]=265;
visited[set<int>{256,2724}]=84;
visited[set<int>{2724,46}]=45;
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

        
        // for 64
        {
            int a = 1000;
            int t = 720;
            int v = 64;
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
9544, 
4079, 
1359, 
8147, 
335, 
5141, 
1461, 
9210, 
10278, 
1906, 
15, 
8309, 
7921, 
9501, 
3690, 
10402, 
1538, 
5289, 
10857, 
377, 
722, 
2501, 
1137, 
7977, 
4780, 
1601, 
10158, 
7659, 
5843, 
3757, 
1590, 
2045, 
1493, 
550, 
1435, 
7538, 
6893, 
8481, 
9677, 
4842, 
2157, 
4936, 
3683, 
3411, 
6330, 
11184, 
9047, 
1925, 
6278, 
2708, 
3564, 
483, 
9672, 
9181, 
603, 
6352, 
10037, 
6644, 
64
            };
            visited[set<int>{4516    ,    7281    }] = 72;
            visited[set<int>{7281,2751}]=10;
visited[set<int>{2751,2239}]=180;
visited[set<int>{2239,7075}]=82;
visited[set<int>{7075,8109}]=73;
visited[set<int>{8109,9480}]=44;
visited[set<int>{9480,9224}]=120;
visited[set<int>{9224,2890}]=133;
visited[set<int>{2890,4501}]=74;
visited[set<int>{4501,8399}]=96;
visited[set<int>{8399,8401}]=36;
visited[set<int>{8401,5819}]=178;
visited[set<int>{5819,9855}]=54;
visited[set<int>{9855,1786}]=37;
visited[set<int>{1786,4581}]=32;
visited[set<int>{4581,10057}]=3;
visited[set<int>{10057,2144}]=31;
visited[set<int>{2144,6125}]=77;
visited[set<int>{6125,3611}]=50;
visited[set<int>{3611,7610}]=174;
visited[set<int>{7610,5953}]=80;
visited[set<int>{5953,10241}]=220;
visited[set<int>{10241,7392}]=23;
visited[set<int>{7392,9074}]=83;
visited[set<int>{9074,155}]=13;
visited[set<int>{155,3924}]=119;
visited[set<int>{3924,9098}]=57;
visited[set<int>{9098,1018}]=62;
visited[set<int>{1018,3295}]=44;
visited[set<int>{3295,3625}]=195;
visited[set<int>{3625,9124}]=15;
visited[set<int>{9124,5515}]=84;
visited[set<int>{5515,9544}]=74;
visited[set<int>{9544,4079}]=73;
visited[set<int>{4079,1359}]=30;
visited[set<int>{1359,8147}]=6;
visited[set<int>{8147,335}]=88;
visited[set<int>{335,5141}]=68;
visited[set<int>{5141,1461}]=60;
visited[set<int>{1461,9210}]=65;
visited[set<int>{9210,10278}]=194;
visited[set<int>{10278,1906}]=258;
visited[set<int>{1906,15}]=203;
visited[set<int>{15,8309}]=255;
visited[set<int>{8309,7921}]=21;
visited[set<int>{7921,9501}]=210;
visited[set<int>{9501,3690}]=74;
visited[set<int>{3690,10402}]=30;
visited[set<int>{10402,1538}]=187;
visited[set<int>{1538,5289}]=86;
visited[set<int>{5289,10857}]=87;
visited[set<int>{10857,377}]=139;
visited[set<int>{377,722}]=57;
visited[set<int>{722,2501}]=48;
visited[set<int>{2501,1137}]=29;
visited[set<int>{1137,7977}]=19;
visited[set<int>{7977,4780}]=46;
visited[set<int>{4780,1601}]=159;
visited[set<int>{1601,10158}]=12;
visited[set<int>{10158,7659}]=14;
visited[set<int>{7659,5843}]=16;
visited[set<int>{5843,3757}]=163;
visited[set<int>{3757,1590}]=97;
visited[set<int>{1590,2045}]=156;
visited[set<int>{2045,1493}]=135;
visited[set<int>{1493,550}]=29;
visited[set<int>{550,1435}]=71;
visited[set<int>{1435,7538}]=9;
visited[set<int>{7538,6893}]=57;
visited[set<int>{6893,8481}]=72;
visited[set<int>{8481,9677}]=255;
visited[set<int>{9677,4842}]=185;
visited[set<int>{4842,2157}]=112;
visited[set<int>{2157,4936}]=16;
visited[set<int>{4936,3683}]=72;
visited[set<int>{3683,3411}]=48;
visited[set<int>{3411,6330}]=226;
visited[set<int>{6330,11184}]=51;
visited[set<int>{11184,9047}]=142;
visited[set<int>{9047,1925}]=232;
visited[set<int>{1925,6278}]=14;
visited[set<int>{6278,2708}]=52;
visited[set<int>{2708,3564}]=26;
visited[set<int>{3564,483}]=109;
visited[set<int>{483,9672}]=80;
visited[set<int>{9672,9181}]=57;
visited[set<int>{9181,603}]=120;
visited[set<int>{603,6352}]=116;
visited[set<int>{6352,10037}]=147;
visited[set<int>{10037,6644}]=35;
visited[set<int>{6644,64}]=73;
    getratio(graph,visited,ratio);
        
while (t < T - a) {
                if (oldV == 4389 && v == 7482) {
                    a = 100;
                }
                int d = graph[v].size();

                vector<int> bias;
                int sum=0;
                for(int i = 0; i < d; ++i) {
                    bias.push_back(func(graph,v,i,ratio));
                    sum += bias[i];
                }
                int rv = ((rand() % sum) + sum) % sum;
                sum = 0;
                int choice = d - 1;
                for (int i = 0; i < d; ++i) {
                    sum += bias[i];
                    if (rv <= sum) {
                        choice = i;
                        break;
                    }
                }
                    if (visited.find(set<int>{v,graph[v][choice][0]}) != visited.end()) {
                        			if((rand()%5==0))
choice = ((rand() % d) + d) % d;
                    }
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

        // 143
        {
            int a = 1000;
            int t = 813;
            int v = 143;
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
1447, 
8451, 
3507, 
8427, 
7199, 
9720, 
2488, 
6566, 
4257, 
1112, 
315, 
1342, 
9307, 
6570, 
3291, 
10752, 
2785, 
7547, 
3773, 
714, 
6344, 
7739, 
3695, 
844, 
2539, 
7973, 
7883, 
8707, 
2791, 
5491, 
9874, 
1993, 
2226, 
7162, 
1987, 
4856, 
9104, 
4959, 
1530, 
3477, 
6309, 
4997, 
106, 
3802, 
8268, 
4228, 
3062, 
10210, 
143};
            visited[set<int>{4516    ,    7281    }] = 72;
visited[set<int>{7281,2751}]=10;
visited[set<int>{2751,2239}]=180;
visited[set<int>{2239,7075}]=82;
visited[set<int>{7075,8109}]=73;
visited[set<int>{8109,9480}]=44;
visited[set<int>{9480,9224}]=120;
visited[set<int>{9224,2890}]=133;
visited[set<int>{2890,4501}]=74;
visited[set<int>{4501,8399}]=96;
visited[set<int>{8399,8401}]=36;
visited[set<int>{8401,5819}]=178;
visited[set<int>{5819,9855}]=54;
visited[set<int>{9855,1786}]=37;
visited[set<int>{1786,4581}]=32;
visited[set<int>{4581,10057}]=3;
visited[set<int>{10057,2144}]=31;
visited[set<int>{2144,6125}]=77;
visited[set<int>{6125,3611}]=50;
visited[set<int>{3611,7610}]=174;
visited[set<int>{7610,5953}]=80;
visited[set<int>{5953,10241}]=220;
visited[set<int>{10241,7392}]=23;
visited[set<int>{7392,9074}]=83;
visited[set<int>{9074,155}]=13;
visited[set<int>{155,3924}]=119;
visited[set<int>{3924,9098}]=57;
visited[set<int>{9098,1018}]=62;
visited[set<int>{1018,3295}]=44;
visited[set<int>{3295,3625}]=195;
visited[set<int>{3625,9124}]=15;
visited[set<int>{9124,5515}]=84;
visited[set<int>{5515,378}]=120;
visited[set<int>{378,3839}]=21;
visited[set<int>{3839,6126}]=19;
visited[set<int>{6126,430}]=173;
visited[set<int>{430,7481}]=149;
visited[set<int>{7481,9578}]=78;
visited[set<int>{9578,4988}]=59;
visited[set<int>{4988,6899}]=64;
visited[set<int>{6899,2049}]=114;
visited[set<int>{2049,1658}]=92;
visited[set<int>{1658,1447}]=66;
visited[set<int>{1447,8451}]=141;
visited[set<int>{8451,3507}]=141;
visited[set<int>{3507,8427}]=140;
visited[set<int>{8427,7199}]=118;
visited[set<int>{7199,9720}]=175;
visited[set<int>{9720,2488}]=198;
visited[set<int>{2488,6566}]=262;
visited[set<int>{6566,4257}]=36;
visited[set<int>{4257,1112}]=77;
visited[set<int>{1112,315}]=167;
visited[set<int>{315,1342}]=33;
visited[set<int>{1342,9307}]=103;
visited[set<int>{9307,6570}]=151;
visited[set<int>{6570,3291}]=78;
visited[set<int>{3291,10752}]=23;
visited[set<int>{10752,2785}]=10;
visited[set<int>{2785,7547}]=8;
visited[set<int>{7547,3773}]=26;
visited[set<int>{3773,714}]=120;
visited[set<int>{714,6344}]=61;
visited[set<int>{6344,7739}]=143;
visited[set<int>{7739,3695}]=142;
visited[set<int>{3695,844}]=128;
visited[set<int>{844,2539}]=204;
visited[set<int>{2539,7973}]=26;
visited[set<int>{7973,7883}]=54;
visited[set<int>{7883,8707}]=38;
visited[set<int>{8707,2791}]=86;
visited[set<int>{2791,5491}]=157;
visited[set<int>{5491,9874}]=9;
visited[set<int>{9874,1993}]=61;
visited[set<int>{1993,2226}]=218;
visited[set<int>{2226,7162}]=109;
visited[set<int>{7162,1987}]=164;
visited[set<int>{1987,4856}]=67;
visited[set<int>{4856,9104}]=158;
visited[set<int>{9104,4959}]=366;
visited[set<int>{4959,1530}]=123;
visited[set<int>{1530,3477}]=37;
visited[set<int>{3477,6309}]=29;
visited[set<int>{6309,4997}]=20;
visited[set<int>{4997,106}]=135;
visited[set<int>{106,3802}]=165;
visited[set<int>{3802,8268}]=53;
visited[set<int>{8268,4228}]=203;
visited[set<int>{4228,3062}]=8;
visited[set<int>{3062,10210}]=20;
visited[set<int>{10210,143}]=10;
    getratio(graph,visited,ratio);
        
            while (t < T - a) {
                if (oldV == 4389 && v == 7482) {
                    a = 100;
                }
                int d = graph[v].size();

                vector<int> bias;
                int sum=0;
                for(int i = 0; i < d; ++i) {
                    bias.push_back(func(graph,v,i,ratio));
                    sum += bias[i];
                }
                int rv = ((rand() % sum) + sum) % sum;
                sum = 0;
                int choice = d - 1;
                for (int i = 0; i < d; ++i) {
                    sum += bias[i];
                    if (rv <= sum) {
                        choice = i;
                        break;
                    }
                }
                    if (visited.find(set<int>{v,graph[v][choice][0]}) != visited.end()) {
                        			if((rand()%5==0))
choice = ((rand() % d) + d) % d;
                    }
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

        // 125
        {
            int a = 1000;
            int t = 1036;
            int v = 125;
            int oldV = v;
            vector<int> path{
4516, 
7281, 
2751, 
2239, 
3878, 
2364, 
3216, 
7851, 
3775, 
5837, 
5431, 
4288, 
3330, 
102, 
8336, 
7120, 
6410, 
8246, 
2512, 
3419, 
3171, 
7138, 
9265, 
3397, 
5465, 
3130, 
10198, 
10140, 
11194, 
5369, 
1160, 
7423, 
8774, 
8863, 
526, 
11024, 
8194, 
5568, 
5831, 
2753, 
4545, 
4490, 
9298, 
4818, 
2416, 
4926, 
2729, 
8203, 
10753, 
10757, 
2243, 
8016, 
2441, 
3224, 
10862, 
8872, 
5496, 
10680, 
341, 
1459, 
1432, 
188, 
1313, 
307, 
11223, 
7391, 
1199, 
2669, 
5278, 
1817, 
6867, 
11333, 
7848, 
5848, 
3101, 
11322, 
10189, 
6458, 
2821, 
6841, 
3358, 
3195, 
792, 
1809, 
8412, 
7337, 
9616, 
2780, 
4754, 
4460, 
8161, 
8957, 
10390, 
9911, 
5611, 
2741, 
2317, 
7665, 
6065, 
7143, 
3759, 
2236, 
9191, 
5433, 
6109, 
6145, 
4634, 
8878, 
7469, 
8140, 
6238, 
8526, 
8038, 
8239, 
9172, 
470, 
5887, 
1863, 
125
            };
            visited[set<int>{4516,           7281,      }] = 72;
           visited[set<int>{7281,2751}]=10;
visited[set<int>{2751,2239}]=180;
visited[set<int>{2239,3878}]=133;
visited[set<int>{3878,2364}]=81;
visited[set<int>{2364,3216}]=288;
visited[set<int>{3216,7851}]=86;
visited[set<int>{7851,3775}]=120;
visited[set<int>{3775,5837}]=79;
visited[set<int>{5837,5431}]=36;
visited[set<int>{5431,4288}]=162;
visited[set<int>{4288,3330}]=163;
visited[set<int>{3330,102}]=54;
visited[set<int>{102,8336}]=22;
visited[set<int>{8336,7120}]=57;
visited[set<int>{7120,6410}]=16;
visited[set<int>{6410,8246}]=126;
visited[set<int>{8246,2512}]=121;
visited[set<int>{2512,3419}]=54;
visited[set<int>{3419,3171}]=93;
visited[set<int>{3171,7138}]=124;
visited[set<int>{7138,9265}]=111;
visited[set<int>{9265,3397}]=36;
visited[set<int>{3397,5465}]=36;
visited[set<int>{5465,3130}]=172;
visited[set<int>{3130,10198}]=141;
visited[set<int>{10198,10140}]=63;
visited[set<int>{10140,11194}]=47;
visited[set<int>{11194,5369}]=123;
visited[set<int>{5369,1160}]=23;
visited[set<int>{1160,7423}]=40;
visited[set<int>{7423,8774}]=277;
visited[set<int>{8774,8863}]=75;
visited[set<int>{8863,526}]=91;
visited[set<int>{526,11024}]=123;
visited[set<int>{11024,8194}]=40;
visited[set<int>{8194,5568}]=36;
visited[set<int>{5568,5831}]=27;
visited[set<int>{5831,2753}]=69;
visited[set<int>{2753,4545}]=42;
visited[set<int>{4545,4490}]=5;
visited[set<int>{4490,9298}]=122;
visited[set<int>{9298,4818}]=213;
visited[set<int>{4818,2416}]=97;
visited[set<int>{2416,4926}]=34;
visited[set<int>{4926,2729}]=12;
visited[set<int>{2729,8203}]=41;
visited[set<int>{8203,10753}]=141;
visited[set<int>{10753,10757}]=109;
visited[set<int>{10757,2243}]=28;
visited[set<int>{2243,8016}]=20;
visited[set<int>{8016,2441}]=43;
visited[set<int>{2441,3224}]=716;
visited[set<int>{3224,10862}]=124;
visited[set<int>{10862,8872}]=19;
visited[set<int>{8872,5496}]=167;
visited[set<int>{5496,10680}]=82;
visited[set<int>{10680,341}]=71;
visited[set<int>{341,1459}]=52;
visited[set<int>{1459,1432}]=34;
visited[set<int>{1432,188}]=120;
visited[set<int>{188,1313}]=65;
visited[set<int>{1313,307}]=15;
visited[set<int>{307,11223}]=73;
visited[set<int>{11223,7391}]=96;
visited[set<int>{7391,1199}]=26;
visited[set<int>{1199,2669}]=50;
visited[set<int>{2669,5278}]=14;
visited[set<int>{5278,1817}]=19;
visited[set<int>{1817,6867}]=45;
visited[set<int>{6867,11333}]=16;
visited[set<int>{11333,7848}]=31;
visited[set<int>{7848,5848}]=39;
visited[set<int>{5848,3101}]=27;
visited[set<int>{3101,11322}]=80;
visited[set<int>{11322,10189}]=72;
visited[set<int>{10189,6458}]=27;
visited[set<int>{6458,2821}]=8;
visited[set<int>{2821,6841}]=50;
visited[set<int>{6841,3358}]=24;
visited[set<int>{3358,3195}]=102;
visited[set<int>{3195,792}]=21;
visited[set<int>{792,1809}]=11;
visited[set<int>{1809,8412}]=105;
visited[set<int>{8412,7337}]=88;
visited[set<int>{7337,9616}]=39;
visited[set<int>{9616,2780}]=44;
visited[set<int>{2780,4754}]=12;
visited[set<int>{4754,4460}]=108;
visited[set<int>{4460,8161}]=91;
visited[set<int>{8161,8957}]=100;
visited[set<int>{8957,10390}]=71;
visited[set<int>{10390,9911}]=93;
visited[set<int>{9911,5611}]=190;
visited[set<int>{5611,2741}]=239;
visited[set<int>{2741,2317}]=161;
visited[set<int>{2317,7665}]=363;
visited[set<int>{7665,6065}]=76;
visited[set<int>{6065,7143}]=36;
visited[set<int>{7143,3759}]=149;
visited[set<int>{3759,2236}]=59;
visited[set<int>{2236,9191}]=41;
visited[set<int>{9191,5433}]=223;
visited[set<int>{5433,6109}]=140;
visited[set<int>{6109,6145}]=239;
visited[set<int>{6145,4634}]=64;
visited[set<int>{4634,8878}]=22;
visited[set<int>{8878,7469}]=27;
visited[set<int>{7469,8140}]=28;
visited[set<int>{8140,6238}]=9;
visited[set<int>{6238,8526}]=229;
visited[set<int>{8526,8038}]=319;
visited[set<int>{8038,8239}]=212;
visited[set<int>{8239,9172}]=52;
visited[set<int>{9172,470}]=32;
visited[set<int>{470,5887}]=297;
visited[set<int>{5887,1863}]=53;
visited[set<int>{1863,125}]=86;
    getratio(graph,visited,ratio);
        
            while (t < T - a) {
                if (oldV == 4389 && v == 7482) {
                    a = 100;
                }
                int d = graph[v].size();
                vector<int> bias;
                int sum=0;
                for(int i = 0; i < d; ++i) {
                    bias.push_back(func(graph,v,i,ratio));
                    sum += bias[i];
                }
                int rv = ((rand() % sum) + sum) % sum;
                sum = 0;
                int choice = d - 1;
                for (int i = 0; i < d; ++i) {
                    sum += bias[i];
                    if (rv <= sum) {
                        choice = i;
                        break;
                    }
                }
                    if (visited.find(set<int>{v,graph[v][choice][0]}) != visited.end()) {
                        			if((rand()%5==0))
choice = ((rand() % d) + d) % d;
                    }
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

// 116
        {
            int a = 1000;
            int t = 996;
            int v = 116;
            int oldV = v;
            vector<int> path{
4516, 
7281, 
2751, 
2239, 
3878, 
2364, 
3216, 
7851, 
3775, 
5837, 
5431, 
4288, 
3330, 
102, 
8336, 
7120, 
6410, 
8246, 
2512, 
3419, 
3171, 
7138, 
9265, 
3397, 
5465, 
3130, 
10198, 
10140, 
11194, 
5369, 
1160, 
7423, 
8774, 
8863, 
526, 
11024, 
8194, 
5568, 
5831, 
2753, 
4545, 
4490, 
9298, 
4818, 
2416, 
4926, 
2729, 
8203, 
10753, 
10757, 
2243, 
8016, 
2441, 
3224, 
10862, 
8872, 
5496, 
11167, 
7633, 
8095, 
623, 
6064, 
7664, 
4483, 
10970, 
2242, 
9520, 
5531, 
7135, 
4466, 
2282, 
8381, 
1100, 
9808, 
9234, 
11173, 
775, 
4690, 
4743, 
5706, 
9917, 
301, 
10203, 
3288, 
78, 
9706, 
4055, 
6504, 
4499, 
2176, 
8894, 
8877, 
6992, 
8069, 
5570, 
7183, 
7533, 
4509, 
1057, 
10253, 
10756, 
5094, 
6661, 
4065, 
8403, 
7613, 
116
            };
visited[set<int>{4516,7281}]=72;
visited[set<int>{7281,2751}]=10;
visited[set<int>{2751,2239}]=180;
visited[set<int>{2239,3878}]=133;
visited[set<int>{3878,2364}]=81;
visited[set<int>{2364,3216}]=288;
visited[set<int>{3216,7851}]=86;
visited[set<int>{7851,3775}]=120;
visited[set<int>{3775,5837}]=79;
visited[set<int>{5837,5431}]=36;
visited[set<int>{5431,4288}]=162;
visited[set<int>{4288,3330}]=163;
visited[set<int>{3330,102}]=54;
visited[set<int>{102,8336}]=22;
visited[set<int>{8336,7120}]=57;
visited[set<int>{7120,6410}]=16;
visited[set<int>{6410,8246}]=126;
visited[set<int>{8246,2512}]=121;
visited[set<int>{2512,3419}]=54;
visited[set<int>{3419,3171}]=93;
visited[set<int>{3171,7138}]=124;
visited[set<int>{7138,9265}]=111;
visited[set<int>{9265,3397}]=36;
visited[set<int>{3397,5465}]=36;
visited[set<int>{5465,3130}]=172;
visited[set<int>{3130,10198}]=141;
visited[set<int>{10198,10140}]=63;
visited[set<int>{10140,11194}]=47;
visited[set<int>{11194,5369}]=123;
visited[set<int>{5369,1160}]=23;
visited[set<int>{1160,7423}]=40;
visited[set<int>{7423,8774}]=277;
visited[set<int>{8774,8863}]=75;
visited[set<int>{8863,526}]=91;
visited[set<int>{526,11024}]=123;
visited[set<int>{11024,8194}]=40;
visited[set<int>{8194,5568}]=36;
visited[set<int>{5568,5831}]=27;
visited[set<int>{5831,2753}]=69;
visited[set<int>{2753,4545}]=42;
visited[set<int>{4545,4490}]=5;
visited[set<int>{4490,9298}]=122;
visited[set<int>{9298,4818}]=213;
visited[set<int>{4818,2416}]=97;
visited[set<int>{2416,4926}]=34;
visited[set<int>{4926,2729}]=12;
visited[set<int>{2729,8203}]=41;
visited[set<int>{8203,10753}]=141;
visited[set<int>{10753,10757}]=109;
visited[set<int>{10757,2243}]=28;
visited[set<int>{2243,8016}]=20;
visited[set<int>{8016,2441}]=43;
visited[set<int>{2441,3224}]=716;
visited[set<int>{3224,10862}]=124;
visited[set<int>{10862,8872}]=19;
visited[set<int>{8872,5496}]=167;
visited[set<int>{5496,11167}]=48;
visited[set<int>{11167,7633}]=154;
visited[set<int>{7633,8095}]=181;
visited[set<int>{8095,623}]=38;
visited[set<int>{623,6064}]=124;
visited[set<int>{6064,7664}]=12;
visited[set<int>{7664,4483}]=131;
visited[set<int>{4483,10970}]=67;
visited[set<int>{10970,2242}]=61;
visited[set<int>{2242,9520}]=41;
visited[set<int>{9520,5531}]=94;
visited[set<int>{5531,7135}]=77;
visited[set<int>{7135,4466}]=83;
visited[set<int>{4466,2282}]=100;
visited[set<int>{2282,8381}]=11;
visited[set<int>{8381,1100}]=34;
visited[set<int>{1100,9808}]=89;
visited[set<int>{9808,9234}]=246;
visited[set<int>{9234,11173}]=250;
visited[set<int>{11173,775}]=96;
visited[set<int>{775,4690}]=86;
visited[set<int>{4690,4743}]=48;
visited[set<int>{4743,5706}]=27;
visited[set<int>{5706,9917}]=109;
visited[set<int>{9917,301}]=174;
visited[set<int>{301,10203}]=59;
visited[set<int>{10203,3288}]=32;
visited[set<int>{3288,78}]=37;
visited[set<int>{78,9706}]=135;
visited[set<int>{9706,4055}]=162;
visited[set<int>{4055,6504}]=26;
visited[set<int>{6504,4499}]=15;
visited[set<int>{4499,2176}]=31;
visited[set<int>{2176,8894}]=60;
visited[set<int>{8894,8877}]=355;
visited[set<int>{8877,6992}]=55;
visited[set<int>{6992,8069}]=71;
visited[set<int>{8069,5570}]=258;
visited[set<int>{5570,7183}]=122;
visited[set<int>{7183,7533}]=28;
visited[set<int>{7533,4509}]=60;
visited[set<int>{4509,1057}]=112;
visited[set<int>{1057,10253}]=112;
visited[set<int>{10253,10756}]=26;
visited[set<int>{10756,5094}]=20;
visited[set<int>{5094,6661}]=32;
visited[set<int>{6661,4065}]=22;
visited[set<int>{4065,8403}]=73;
visited[set<int>{8403,7613}]=106;
visited[set<int>{7613,116}]=224;
    getratio(graph,visited,ratio);
        
            while (t < T - a) {
                if (oldV == 4389 && v == 7482) {
                    a = 100;
                }
                int d = graph[v].size();
                vector<int> bias;
                int sum=0;
                for(int i = 0; i < d; ++i) {
                    bias.push_back(func(graph,v,i,ratio));
                    sum += bias[i];
                }
                int rv = ((rand() % sum) + sum) % sum;
                sum = 0;
                int choice = d - 1;
                for (int i = 0; i < d; ++i) {
                    sum += bias[i];
                    if (rv <= sum) {
                        choice = i;
                        break;
                    }
                }
                    if (visited.find(set<int>{v,graph[v][choice][0]}) != visited.end()) {
                       			if((rand()%5==0))
 choice = ((rand() % d) + d) % d;
                    }
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


// 140
        {
            int a = 1000;
            int t = 610;
            int v = 140;
            int oldV = v;
            vector<int> path{4516, 
7281, 
2751, 
2239, 
3878, 
2364, 
3216, 
7851, 
2723, 
11107, 
10530, 
10154, 
2094, 
656, 
1126, 
7030, 
3046, 
313, 
9723, 
6707, 
3164, 
7163, 
9696, 
9080, 
5504, 
7417, 
8664, 
4593, 
6934, 
6380, 
9378, 
4670, 
9375, 
5453, 
1110, 
5927, 
4656, 
9267, 
2902, 
2919, 
10846, 
5346, 
10462, 
3790, 
4726, 
3011, 
411, 
10083, 
4348, 
1652, 
4475, 
6462, 
9221, 
140
            };
visited[set<int>{4516,7281}]=72;
visited[set<int>{7281,2751}]=10;
visited[set<int>{2751,2239}]=180;
visited[set<int>{2239,3878}]=133;
visited[set<int>{3878,2364}]=81;
visited[set<int>{2364,3216}]=288;
visited[set<int>{3216,7851}]=86;
visited[set<int>{7851,2723}]=71;
visited[set<int>{2723,11107}]=316;
visited[set<int>{11107,10530}]=199;
visited[set<int>{10530,10154}]=100;
visited[set<int>{10154,2094}]=107;
visited[set<int>{2094,656}]=35;
visited[set<int>{656,1126}]=78;
visited[set<int>{1126,7030}]=86;
visited[set<int>{7030,3046}]=120;
visited[set<int>{3046,313}]=123;
visited[set<int>{313,9723}]=34;
visited[set<int>{9723,6707}]=89;
visited[set<int>{6707,3164}]=82;
visited[set<int>{3164,7163}]=81;
visited[set<int>{7163,9696}]=67;
visited[set<int>{9696,9080}]=105;
visited[set<int>{9080,5504}]=96;
visited[set<int>{5504,7417}]=115;
visited[set<int>{7417,8664}]=60;
visited[set<int>{8664,4593}]=84;
visited[set<int>{4593,6934}]=42;
visited[set<int>{6934,6380}]=62;
visited[set<int>{6380,9378}]=82;
visited[set<int>{9378,4670}]=125;
visited[set<int>{4670,9375}]=372;
visited[set<int>{9375,5453}]=145;
visited[set<int>{5453,1110}]=106;
visited[set<int>{1110,5927}]=59;
visited[set<int>{5927,4656}]=193;
visited[set<int>{4656,9267}]=464;
visited[set<int>{9267,2902}]=12;
visited[set<int>{2902,2919}]=422;
visited[set<int>{2919,10846}]=243;
visited[set<int>{10846,5346}]=237;
visited[set<int>{5346,10462}]=60;
visited[set<int>{10462,3790}]=46;
visited[set<int>{3790,4726}]=245;
visited[set<int>{4726,3011}]=25;
visited[set<int>{3011,411}]=84;
visited[set<int>{411,10083}]=58;
visited[set<int>{10083,4348}]=83;
visited[set<int>{4348,1652}]=117;
visited[set<int>{1652,4475}]=21;
visited[set<int>{4475,6462}]=161;
visited[set<int>{6462,9221}]=27;
visited[set<int>{9221,140}]=16;
    getratio(graph,visited,ratio);
        
            while (t < T - a) {
                if (oldV == 4389 && v == 7482) {
                    a = 100;
                }
                int d = graph[v].size();
                vector<int> bias;
                int sum=0;
                for(int i = 0; i < d; ++i) {
                    bias.push_back(func(graph,v,i,ratio));
                    sum += bias[i];
                }
                int rv = ((rand() % sum) + sum) % sum;
                sum = 0;
                int choice = d - 1;
                for (int i = 0; i < d; ++i) {
                    sum += bias[i];
                    if (rv <= sum) {
                        choice = i;
                        break;
                    }
                }
                    if (visited.find(set<int>{v,graph[v][choice][0]}) != visited.end()) {
                        			if((rand()%5==0))
choice = ((rand() % d) + d) % d;
                    }
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


// 225
        {
            int a = 1000;
            int t = 195;
            int v = 225;
            int oldV = v;
            vector<int> path{4516, 
1032, 
3655, 
7680, 
397, 
4679, 
5610, 
6502, 
4318, 
8098, 
3820, 
4700, 
3237, 
5330, 
366, 
3121, 
10611, 
8590, 
5368, 
225
            };
visited[set<int>{4516,1032}]=389;
visited[set<int>{1032,3655}]=15;
visited[set<int>{3655,7680}]=210;
visited[set<int>{7680,397}]=157;
visited[set<int>{397,4679}]=20;
visited[set<int>{4679,5610}]=36;
visited[set<int>{5610,6502}]=118;
visited[set<int>{6502,4318}]=88;
visited[set<int>{4318,8098}]=27;
visited[set<int>{8098,3820}]=102;
visited[set<int>{3820,4700}]=134;
visited[set<int>{4700,3237}]=155;
visited[set<int>{3237,5330}]=107;
visited[set<int>{5330,366}]=114;
visited[set<int>{366,3121}]=100;
visited[set<int>{3121,10611}]=126;
visited[set<int>{10611,8590}]=108;
visited[set<int>{8590,5368}]=98;
visited[set<int>{5368,225}]=172;
    getratio(graph,visited,ratio);
        
            while (t < T - a) {
                if (oldV == 4389 && v == 7482) {
                    a = 100;
                }
                int d = graph[v].size();
                vector<int> bias;
                int sum=0;
                for(int i = 0; i < d; ++i) {
                    bias.push_back(func(graph,v,i,ratio));
                    sum += bias[i];
                }
                int rv = ((rand() % sum) + sum) % sum;
                sum = 0;
                int choice = d - 1;
                for (int i = 0; i < d; ++i) {
                    sum += bias[i];
                    if (rv <= sum) {
                        choice = i;
                        break;
                    }
                }
                    if (visited.find(set<int>{v,graph[v][choice][0]}) != visited.end()) {
                        choice = ((rand() % d) + d) % d;
                    }
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


// 247
        {
            int a = 1000;
            int t = 977;
            int v = 247;
            int oldV = v;
            vector<int> path{4516, 
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
8516, 
3464, 
2419, 
7661, 
4635, 
127, 
241, 
4156, 
752, 
2732, 
4235, 
10225, 
6832, 
8981, 
5050, 
9478, 
6560, 
219, 
4916, 
719, 
10860, 
5419, 
8279, 
5698, 
8831, 
6364, 
9568, 
2527, 
6225, 
3852, 
8855, 
298, 
109, 
9119, 
732, 
9482, 
7806, 
4989, 
1627, 
2630, 
7157, 
2278, 
9060, 
5115, 
195, 
9447, 
8462, 
1305, 
1052, 
7884, 
9458, 
461, 
11058, 
5922, 
11277, 
2351, 
5560, 
3006, 
5719, 
3348, 
7554, 
5519, 
3362, 
8334, 
6664, 
7116, 
7785, 
7870, 
247
            };
visited[set<int>{4516,7281}]=72;
visited[set<int>{7281,2751}]=10;
visited[set<int>{2751,2239}]=180;
visited[set<int>{2239,7075}]=82;
visited[set<int>{7075,8109}]=73;
visited[set<int>{8109,9480}]=44;
visited[set<int>{9480,9224}]=120;
visited[set<int>{9224,2890}]=133;
visited[set<int>{2890,4501}]=74;
visited[set<int>{4501,8399}]=96;
visited[set<int>{8399,8401}]=36;
visited[set<int>{8401,5819}]=178;
visited[set<int>{5819,9855}]=54;
visited[set<int>{9855,1786}]=37;
visited[set<int>{1786,4581}]=32;
visited[set<int>{4581,10057}]=3;
visited[set<int>{10057,2144}]=31;
visited[set<int>{2144,6125}]=77;
visited[set<int>{6125,3611}]=50;
visited[set<int>{3611,7610}]=174;
visited[set<int>{7610,5953}]=80;
visited[set<int>{5953,10241}]=220;
visited[set<int>{10241,7392}]=23;
visited[set<int>{7392,8516}]=78;
visited[set<int>{8516,3464}]=83;
visited[set<int>{3464,2419}]=83;
visited[set<int>{2419,7661}]=30;
visited[set<int>{7661,4635}]=619;
visited[set<int>{4635,127}]=86;
visited[set<int>{127,241}]=337;
visited[set<int>{241,4156}]=76;
visited[set<int>{4156,752}]=14;
visited[set<int>{752,2732}]=19;
visited[set<int>{2732,4235}]=26;
visited[set<int>{4235,10225}]=76;
visited[set<int>{10225,6832}]=27;
visited[set<int>{6832,8981}]=186;
visited[set<int>{8981,5050}]=13;
visited[set<int>{5050,9478}]=173;
visited[set<int>{9478,6560}]=14;
visited[set<int>{6560,219}]=423;
visited[set<int>{219,4916}]=110;
visited[set<int>{4916,719}]=31;
visited[set<int>{719,10860}]=15;
visited[set<int>{10860,5419}]=48;
visited[set<int>{5419,8279}]=18;
visited[set<int>{8279,5698}]=53;
visited[set<int>{5698,8831}]=79;
visited[set<int>{8831,6364}]=75;
visited[set<int>{6364,9568}]=64;
visited[set<int>{9568,2527}]=294;
visited[set<int>{2527,6225}]=129;
visited[set<int>{6225,3852}]=162;
visited[set<int>{3852,8855}]=755;
visited[set<int>{8855,298}]=79;
visited[set<int>{298,109}]=245;
visited[set<int>{109,9119}]=65;
visited[set<int>{9119,732}]=67;
visited[set<int>{732,9482}]=114;
visited[set<int>{9482,7806}]=116;
visited[set<int>{7806,4989}]=37;
visited[set<int>{4989,1627}]=103;
visited[set<int>{1627,2630}]=147;
visited[set<int>{2630,7157}]=275;
visited[set<int>{7157,2278}]=55;
visited[set<int>{2278,9060}]=16;
visited[set<int>{9060,5115}]=52;
visited[set<int>{5115,195}]=67;
visited[set<int>{195,9447}]=186;
visited[set<int>{9447,8462}]=19;
visited[set<int>{8462,1305}]=24;
visited[set<int>{1305,1052}]=195;
visited[set<int>{1052,7884}]=26;
visited[set<int>{7884,9458}]=55;
visited[set<int>{9458,461}]=74;
visited[set<int>{461,11058}]=70;
visited[set<int>{11058,5922}]=59;
visited[set<int>{5922,11277}]=79;
visited[set<int>{11277,2351}]=72;
visited[set<int>{2351,5560}]=21;
visited[set<int>{5560,3006}]=6;
visited[set<int>{3006,5719}]=170;
visited[set<int>{5719,3348}]=105;
visited[set<int>{3348,7554}]=67;
visited[set<int>{7554,5519}]=130;
visited[set<int>{5519,3362}]=16;
visited[set<int>{3362,8334}]=144;
visited[set<int>{8334,6664}]=137;
visited[set<int>{6664,7116}]=68;
visited[set<int>{7116,7785}]=116;
visited[set<int>{7785,7870}]=205;
visited[set<int>{7870,247}]=77;
    getratio(graph,visited,ratio);
        
            while (t < T - a) {
                if (oldV == 4389 && v == 7482) {
                    a = 100;
                }
                int d = graph[v].size();
                vector<int> bias;
                int sum=0;
                for(int i = 0; i < d; ++i) {
                    bias.push_back(func(graph,v,i,ratio));
                    sum += bias[i];
                }
                int rv = ((rand() % sum) + sum) % sum;
                sum = 0;
                int choice = d - 1;
                for (int i = 0; i < d; ++i) {
                    sum += bias[i];
                    if (rv <= sum) {
                        choice = i;
                        break;
                    }
                }
                    if (visited.find(set<int>{v,graph[v][choice][0]}) != visited.end()) {
                       			if((rand()%5==0))
 choice = ((rand() % d) + d) % d;
                    }
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
