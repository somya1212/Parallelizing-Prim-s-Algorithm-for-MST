#include <iostream>
#include <vector>
#include <cuda.h>
#include <thrust/device_vector.h>
#include <thrust/extrema.h>
#include <thrust/device_free.h>
#include <ctime>
using namespace std;

int main(){
    int nodes, edges;
    cin>>nodes>>edges;
    vector<vector<pair<int,int> > > adjacency_list(nodes); 
    for(int i = 0; i < edges; ++i){
        int node1, node2, weight;
        cin>>node1>>node2>>weight;
        adjacency_list[node1].push_back(make_pair(node2, weight));
        adjacency_list[node2].push_back(make_pair(node1, weight));
    }
    int * V = new int[nodes];
    int * E = new int[2 * edges];
    int * W = new int[2 * edges];
    int cumulative_sum = 0, limit;
    for(int i = 0; i < nodes; ++i){
        V[i] = cumulative_sum;
        limit = adjacency_list[i].size();
        for(int j = 0; j < limit; ++j){
            E[cumulative_sum + j] = adjacency_list[i][j].first;
            W[cumulative_sum + j] = adjacency_list[i][j].second;
        }
        cumulative_sum += limit;
    }
    
    long long int edge_sum = 0;
    int current = 0;
     int count = 0;

    int *parent = new int[nodes];
    vector<int> weights(nodes);
    bool *inMST = new bool[nodes];
    parent[0] = -1;
    for(int i = 0; i < nodes; ++i) {
        weights[i] = INT_MAX;
        inMST[i] = false;
    }
    // device vector for the weights array
    thrust::device_vector<int> device_weights(weights.begin(), weights.end());
    thrust::device_ptr<int> ptr = device_weights.data();
    clock_t begin = clock();
    while(count < nodes-1){
        ++count;
        inMST[current] = true;
        int len = adjacency_list[current].size();
        for(int i = 0; i < len; ++i) {
            int incoming_vertex = adjacency_list[current][i].first;
            if(!inMST[incoming_vertex]) {
                if(weights[incoming_vertex] > adjacency_list[current][i].second) {
                    weights[incoming_vertex] = adjacency_list[current][i].second;
                    parent[incoming_vertex] = current;
                }
            }
        }
        device_weights = weights;
       int min_index = thrust::min_element(ptr, ptr + nodes) - ptr;
        cout<<"Min Weight Index: "<<min_index<<endl;
        
        parent[min_index] = current;
        edge_sum += weights[min_index];
        weights[min_index] = INT_MAX;
        // new current 
        current = min_index;      
    }
    clock_t end = clock();
    cout<<"Sum of Edges in MST: "<<edge_sum<<endl;
    double elapsed_time = double(end - begin);
    cout<<"Execution time: "<<elapsed_time<<endl;
    free(V); free(E); free(W);
    free(parent); free(inMST); 
    return 0;
}
