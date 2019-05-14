#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

#define pb push_back
#define ff first
#define ss second
typedef long long Long;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<Long> vl;
typedef unsigned int ui;
typedef pair<int, ui> piui;

enum SpanningTreeType { MIN, MAX };

// Prim's algorithm to compute Min/Max Spanning Tree
class SpanningTree {
private:
	SpanningTreeType type;
	vector< vector<piui> > adjacencyList;
	// Array to store constructed MST 
	vector< int > parent;
	// Key values used to pick minimum weight edge in cut 
	vector< int > key;
	// To represent set of vertices not yet included in MST 
	vector< bool > mstSet;
	int V;

	bool Compare(int a, int b) {
		if(type == MAX)
			return a < b;
		else
			return a > b;
	}

	// A utility function to find the vertex with  
	// minimum/maximum key value, from the set of vertices  
	// not yet included in MST 
	int minMaxKey(vector< int > *_key, vector< bool > *_mstSet) {
		int result = (type == MIN) ? INT_MAX : INT_MIN, index = 0;
		for(int v=0; v<V; v++) {
			// printf("key[ %d ]= %d\n", v, _key->at(v));
			if( _mstSet->at(v) == false && Compare(result, _key->at(v)) )
				result = _key->at(v), index = v;
		}
		return index;
	}

public:
	SpanningTree(SpanningTreeType _type, int n) : type(_type) {
		V = n;

		vector< piui > ll;
		adjacencyList.clear();
		adjacencyList.assign(n, ll);

		int keyVal = (_type == MIN) ? INT_MAX : INT_MIN;
		parent.assign(V, -1);
		key.assign(V, keyVal);
		mstSet.assign(V, false);
	}

	// Add weighted edge to graph
	void AddEdge(int i, int j, int weight) {
		piui iedge(j, weight), jedge(i, weight);
		adjacencyList[i].push_back(iedge);
		adjacencyList[j].push_back(jedge);
	}

	// Function to construct and print MST for  
	// a graph represented using adjacency  
	// matrix representation 
	unsigned long int PrimMST() {
	    // Always include first 1st vertex in MST. 
	    // Make key 0 so that this vertex is picked as first vertex. 
	    key[0] = 0;      
	    parent[0] = -1; // First node is always root of MST  
	  
	    // The MST will have V vertices 
	    for (int count = 0; count < V-1; count++) 
	    { 
	        // Pick the minimum key vertex from the  
	        // set of vertices not yet included in MST 
	        int u = minMaxKey(&key, &mstSet); 
	        // printf("Visiting %d, key[%d] = %d\n", u, u, key[u]);
	  
	        // Add the picked vertex to the MST Set 
	        mstSet[u] = true;
	  
	        // Update key value and parent index of  
	        // the adjacent vertices of the picked vertex.  
	        // Consider only those vertices which are not  
	        // yet included in MST 
	        for (int ni = 0; ni < adjacencyList[u].size(); ni++) {
	        	piui neighbour = adjacencyList[u][ni];
	        	int neighbourIndex = neighbour.first;
	        	int neighbourWeight = neighbour.second;
	        	// int compareRes = Compare(key[neighbourIndex], neighbourWeight);
	        	// printf("Updating (%d, %d), Weight %d, key[ %d ] = %d, compareRes = %d\n", u, neighbourIndex, neighbourWeight, neighbourIndex, key[neighbourIndex], compareRes);

		        // graph[u][v] is non zero only for adjacent vertices of m 
		        // mstSet[v] is false for vertices not yet included in MST 
		        // Update the key only if graph[u][v] is smaller than key[v] 
		        if ( mstSet[neighbourIndex] == false && Compare(key[neighbourIndex], neighbourWeight) )
		            parent[neighbourIndex] = u, key[neighbourIndex] = neighbourWeight; 
		     }
	    }

	    unsigned long int sum = 0;
	    for(int v=0; v<V; v++)
	    	sum = sum + key[v];

	    // PrintMST();
	    return sum;
	}

	void PrintMST() {
		for(int i=1; i<V; i++) {
			printf("Edge (%d, %d), Weight %d\n", i, parent[i], key[i]);
		}
	}
};

int main() {
	int TC, N, M, U, V, T;
	cin >> TC;
	for(int i=0; i<TC; i++) {
		cin >> N >> M;
		SpanningTree s(MAX, N);
		for(int j=0; j<M; j++) {
			cin >> U >> V >> T;
			U--; V--;
			// printf("Input Edge (%d, %d), Weight (%d)\n", U, V, T);
			s.AddEdge(U, V, T);
		}
		unsigned long int sum = s.PrimMST();
		cout << sum << endl;
	}
	return 0;
}