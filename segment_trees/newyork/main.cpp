#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template<typename T> int maxf(T a, T b) { if (a > b) return a; return b; }
template<typename T> int minf(int a, int b) { if (a < b) return a; return b; }

enum PriorityQueueType { MIN, MAX };

template<typename T> class PriorityQueue {
private:
	vector<T*> queue;
    int size;
    PriorityQueueType type;
    less<T> L;
    greater<T> G;

public:
	PriorityQueue(PriorityQueueType queueType) {
		size = 0;
		type = queueType;
		L = less<T>();
		G = greater<T>();
		queue.push_back(0); // 1-based array
	}

	void Swap(int x, int y) {
		T* temp = queue[x];
		queue[x] = queue[y];
		queue[y] = temp;
	}

	bool Compare(int x, int y) {
		if(type == MAX)
			return L(*queue[x], *queue[y]);
		else
			return G(*queue[x], *queue[y]);
	}

	int Parent(int k) { return k >> 1; }
	int Left(int k) { return k << 1; }
	int Right(int k) { return (k << 1) + 1; }

	void Swim(int k) {
		int parentk = Parent(k);
		while(k > 1 && Compare(parentk, k)) {
			Swap(parentk, k);
			k = parentk;
			parentk = Parent(k);
		}
	}

	void Sink(int k) {
		int leftk = Left(k);
		int rightk = Right(k);
		while(leftk <= size) {
			int child = leftk;
			if(rightk <= size) child = Compare(leftk, rightk) ? rightk : leftk;
			if(Compare(child, k)) break;
			Swap(k, child);
			k = child;
			leftk = Left(child);
			rightk = Right(child);
		}
	}

	void Add(T* x) {
		queue.push_back(x);
		size++;
		if(size > 1)
			Swim(size);
	}

	T* Pop() {
		T* top = queue[1];
		queue[1] = queue[size];
		queue.pop_back();
		size--;
		Sink(1);
		return top;
	}

	T* Peek() {
		return queue[1];
	}

	void Print() {
		cout << "size: " << size << "\n";
		for(int k=1; k<=size; k++) {
			cout << queue[k]->ToString() << "\n";
		}
	}
	void PrintA() {
		cout << "size: " << size << "\n";
		for(int k=1; k<=size; k++) {
			cout << *queue[k] << "\n";
		}
	}

	int GetSize() {
		return size;
	}

	vector<int> GetQueue() {
		vector<int> v;
		for(int i=1; i<=size; i++)
			v.push_back(*queue[i]);
		return v;
	}
};

struct Node {
	int l, r;
	int mid;
	int maxheight;
	Node* left;
	Node* right;
	Node() { l = 0; r = 0; mid = 0; maxheight = 0; left = NULL; right = NULL; }
	Node(int _l, int _r, int _mid, int _maxheight, Node* ln, Node* rn) { 
		l = _l;
		r = _r;
		mid = _mid;
		maxheight = _maxheight;
		left = ln;
		right = rn; 
	}
};

struct Building {
	int l, r, h;
	Building(int _l, int _r, int _h) { l = _l; r = _r; h = _h; }
};

class SegmentTree {
private:
	PriorityQueue<int>* X;
	Node* root;
	int size;

	vector<Node*> GetLeaves();
	void BuildTree(vector<Node*> &leaves);
	bool IsOverlap(Node *n, int bl, int br);
	int AddBuildingInternal(Node* n, int bl, int br, int bh);
public:
	SegmentTree(PriorityQueue<int> *x) {
		X = x;
		size = X->GetSize();
		vector<Node*> leaves = GetLeaves();
		BuildTree(leaves);
	}

	int AddBuilding(int bl, int br, int bh);
};

// Get a list of leaf nodes from a list of values to build the segment tree from
vector<Node*> SegmentTree::GetLeaves() {
	vector<Node*> leaves;
	int size = X->GetSize();
	for(int i=0; i<size-1; i++) {
		int *l = X->Pop(), *r = l;
		if(i+1 < size) r = X->Peek();
		Node* n = new Node(*l, *r, -1, 0, NULL, NULL);
		// cout << *l << " " << *r << endl;
		leaves.push_back(n);
	}
	return leaves;
}

// Build segment tree from bottom up with leaves array
void SegmentTree::BuildTree(vector<Node*> &leaves) {
	while(leaves.size() > 1) {
		vector<Node*> nextLevel;
		for(int i=0; i<leaves.size(); i+=2) {
			Node *l = leaves[i], *r = leaves[i];
			Node* n;
			if(i+1 < leaves.size()) {
				r = leaves[i+1];
				n = new Node(l->l, r->r, l->r, 0, l, r);
			} else {
				n = l;
			}
			nextLevel.push_back(n);
		}
		leaves = nextLevel;
	}
	root = leaves[0];
}

// Check if a building overlaps with a segment tree range node or not
bool SegmentTree::IsOverlap(Node *n, int bl, int br) {
	if(bl <= n->r && br >= n->l) return true;
	return false;
}

int SegmentTree::AddBuilding(int bl, int br, int bh) {
	return AddBuildingInternal(root, bl, br, bh);
}

// Add a building to the segment tree and get the overlapping sum
int SegmentTree::AddBuildingInternal(Node* n, int bl, int br, int bh) {
	if(bl > n->r || br < n->l) return 0;

	int overlap = 0;

	// If current node's range fully falls within new building's range
	if(bl <= n->l && br >= n->r) {
		// cout << "current range: " << n->l << " " << n->r << " building: " << bl << " " << br << endl;
		if(n->maxheight <= bh) {
			n->maxheight = bh;
			if(n->left == NULL && n->right == NULL)
				overlap = n->r - n->l;
		}
	}
	if(n->left != NULL && IsOverlap(n->left, bl, br))
		overlap = overlap + AddBuildingInternal(n->left, bl, br, bh);
	if(n->left != NULL && IsOverlap(n->right, bl, br))
		overlap = overlap + AddBuildingInternal(n->right, bl, br, bh);
	return overlap;
}

int main() {
	int c, n;
	cin >> c;
	for(int t=0; t<c; t++) {
		cin >> n;
		vector<Building*> bs;
		vector<int> L, R, H;
		PriorityQueue<int>* ends = new PriorityQueue<int>(MIN);
		for(int k=0; k<n; k++) {
			int l=0, r=0, h=0;
			cin >> l >> r >> h;
			L.push_back(l);
			R.push_back(r);
			H.push_back(h);
			int *pl = new int, *pr = new int;
			*pl = l; *pr = r;
			ends->Add(pl);
			ends->Add(pr);
		}
		SegmentTree st(ends);
		int totalOverlap = 0;
		for(int k=0; k<n; k++) {
			totalOverlap = totalOverlap + st.AddBuilding(L[k], R[k], H[k]);
			// cout << "k: " << k << " overlap: " << totalOverlap << endl;
		}
		cout << totalOverlap << endl;
	}
	cin >> c;
	return 0;
}