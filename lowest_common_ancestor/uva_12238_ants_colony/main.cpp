// Weighted Lowest Common Ancestor / Range Minimum Query
// Input: Tree with edge weights
// Output: LCA of 2 nodes in tree and shortest distance b/w 2 nodes
// Space complexity: O(3 * (2N-1)) + O(3 * N) + O(2*(2N-1)-1) = O(6N-3 + 3N + 4N-3) = O(13N - 6)
// Run complexity:
	// Build: EulerTour: O(2N-1), SegmentTreeBuild: O(4N-2)
	// Query: O(log(2N-1))
	// Overall: O(6N-3 + log(2N-1)) = O(N + log(N)) = O(N)

#include <iostream>
#include <vector>
#include <utility>

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

struct Node {
	int l, r;
	int mid;
	long int val;
	Node* left;
	Node* right;
	Node() { l = 0; r = 0; mid = 0; val = 0; left = NULL; right = NULL; }
	Node(int _l, int _r, int _mid, int _val, Node* ln, Node* rn) { 
		l = _l;
		r = _r;
		mid = _mid;
		val = _val;
		left = ln;
		right = rn; 
	}
};

class MinSegmentTree {
private:
	vi X;
	Node* root;
	int size;

	vector<Node*> getLeaves() {
		vector<Node*> leaves(size);
		for(int i=0; i<size; i++) {	
			Node *n = new Node(i, i, -1, i, NULL, NULL);
			leaves[i] = n;
		}
		return leaves;
	}

	void buildTree(vector<Node*> leaves) {
		while(leaves.size() > 1) {
			int levelSize = (int)leaves.size();
			int nextLevelSize = int(levelSize/2);
			vector<Node*> nextLevel;
			for(int i=0; i<levelSize; i+=2) {
				Node *left = leaves.at(i), *n;
				if(i+1<levelSize) {
					Node *right = leaves.at(i+1);
					int minIndex = (X.at(right->val) <= X.at(left->val)) ? right->val : left->val;
					n = new Node(left->l, right->r, left->r, minIndex, left, right);
				} else {
					n = left;
				}
				nextLevel.push_back(n);
			}
			leaves = nextLevel;
		}
		root = leaves.at(0);
	}

	// Query for min in range i to j
	int rmq(Node *n, int i, int j) {
		if(i > n->r || j < n->l) return -1;
		if(i <= n->l && n->r <= j) return n->val;

		int p1 = -1, p2 = -1;
		if(n->left != NULL) p1 = rmq(n->left, i, j);
		if(n->right != NULL) p2 = rmq(n->right, i, j);
		if(p1 == -1) return p2;
		if(p2 == -1) return p1;
		return (X.at(p2) <= X.at(p1)) ? p2 : p1;
	}
	void print(Node *n) {
		cout << "l: " << n->l << ", r: " << n->r << ", v: " << n->val << endl;
		if(n->left != NULL) print(n->left);
		if(n->right != NULL) print(n->right);
	}
public:
	MinSegmentTree() {

	}

	void Build(vector<int> x) {
		X = x;
		size = X.size();
		vector<Node*> leaves = getLeaves();
		buildTree(leaves);
	}

	int Rmq(int i, int j) { return rmq(root, i, j); }
	void Print() { print(root); }
};

class WeightedLCA {
private:
	int rootIndex;
	// Space complexity: O(3 * (2N-1)) + O(3 * N) + O(2*(2N-1)-1) = O(6N-3 + 3N + 4N-3) = O(13N - 6)
	vector< vector< piui > > adjacencyList;

	// LCA data structures: Euler tour, Levels of indices in euler tour, first occurence 
	vi E, L, H;
	vb V;
	vl weights;
	MinSegmentTree st;

	// Perform euler tour of tree 
	void eulerTour(int n, int parent, Long edgeweight, int h) {
		H[n] = (int)E.size();
		E.push_back(n);
		L.push_back(h);
		weights[n] = weights[parent] + edgeweight;
		V[n] = true;
		for(int i=0; i<adjacencyList[n].size(); i++) {
			piui child = adjacencyList[n][i];
			if(V[child.first]) continue;
			eulerTour(child.first, n, child.second, h+1);
			E.push_back(n);
			L.push_back(h);
		}
	}
public:
	WeightedLCA(int n) {
		adjacencyList.clear(); E.clear(); L.clear(); H.clear();
		vector< piui > ll;
		adjacencyList.assign(n, ll);
		H.assign(n, 0);
		weights.assign(n, 0);
		V.assign(n, false);
	}

	// Build tree on which we need to perform LCA
	void AddEdge(int i, int j, long long int Li) {
		piui iedge(j, Li), jedge(i, Li);
		adjacencyList[i].push_back(iedge);
		adjacencyList[j].push_back(jedge);
	}

	void Build(int r) {
		rootIndex = r; // Set root index
		eulerTour(rootIndex, 0, 0, 1);
		st.Build(L);
	}

	int GetLCA(int a, int b) {
		int sti = H[a], stj = H[b];
		if(stj < sti) {int t = sti; sti = stj; stj = t; }
		int minLevelEulerIndex = st.Rmq(sti, stj);
		return E[minLevelEulerIndex];
	}

	Long ShortestPath(int a, int b) {
		int lca = GetLCA(a, b);
		Long shortestPath = (weights[a] - weights[lca]) + (weights[b] - weights[lca]);
		return shortestPath;
	}

	void Print() {
		for(int i=0; i<(int)E.size(); i++)
			cout << E[i] << " ";
		cout << endl;
		for(int i=0; i<(int)L.size(); i++)
			cout << L[i] << " ";
		cout << endl;
		for(int i=0; i<(int)H.size(); i++)
			cout << H[i] << " ";
		cout << endl;
	}
};

int main() {
	int N, Ai, Q, S, T;
	Long Li;
	while(cin >> N) {
		if(N == 0) break;
		WeightedLCA l(N);
		for(int i=1; i<N; i++) {
			cin >> Ai >> Li;
			l.AddEdge(i, Ai, Li);
		}
		l.Build(0);
		cin >> Q;
		for(int i=0; i<Q; i++) {
			cin >> S >> T;
			Long shortestPath = l.ShortestPath(S, T);
			cout << shortestPath;
			if(i < Q-1) cout << " ";
		}
		cout << endl;
	}
	return 0;
}