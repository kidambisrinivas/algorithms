#include <iostream>
#include <vector>

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

int main() {
	return 0;
}