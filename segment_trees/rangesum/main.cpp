#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

class SumSegmentTree {
private:
	vector<int> st;
	vector<int> *A;
	int n, stSize;

	// O(n)
	void build(int p, int L, int R) {
		// as L == R, either one is fine
		if(L == R) {
			st[p] = (*A)[L];	// store the index
		} else {
			// recursively compute the values
			int mid = (L+R)/2;
			int left = Left(p), right = Right(p);
			build(left, L, mid);
			build(right, mid+1, R);
			int p1 = st[left], p2 = st[right];
			st[p] = p1 + p2;
		}
	}

	void updateRmq(int p, int L, int R, int i, int j, int diff) {
		// Base Case: If the input index lies outside the range of
		// this segment
		if(i > R || j < L) return;		// current segment outside query range
		if(L == R) {
			if(L >= i && L <= j) {
				st[p] = st[p] + diff;
			}
			return;
		}

		// If the input index is in range of this node, then update
		// the value of the node and its children
		int mid = (L+R)/2;
		int left = Left(p), right = Right(p);
		updateRmq(left, L, mid, i, j, diff);
		updateRmq(right, mid+1, R, i, j, diff);
		st[p] = st[left] + st[right];
	}

	// O(log n)
	int rmq(int p, int L, int R, int i, int j) {
		if(i > R || j < L) return -1;		// current segment outside query range
		if(i <= L && R <= j) return st[p];	// inside query range

		// compute the max position in the left and right part of the interval
		int mid = (L+R)/2;
		int left = Left(p), right = Right(p);
		int p1 = rmq(left, L, mid, i, j);
		int p2 = rmq(right, mid+1, R, i, j);

		// if we try to access segment outside query
		if(p1 == -1) return p2;
		if(p2 == -1) return p1;

		return p1 + p2;	// as in build routine
	}
public:
	int Left(int p) { return p << 1; }
	int Right(int p) { return (p << 1) + 1; }

	SumSegmentTree(vector<int> *_A) {
		A = _A; n = (int)A->size();
		stSize = int(pow(2,ceil(log2(double(2*n)))));
		st.assign(stSize, 0);
		build(1, 0, n-1);
	}

	void print() {
		for(int x=0; x<st.size(); x++)
			cout << x << ": " << st[x] << "\n";
	}

	void update(int i, int j, int diff) {
		for(int x=i; x<=j; x++)
			(*A)[x] = (*A)[x] + diff;
		updateRmq(1, 0, n-1, i, j, diff);
	}

	int Rmq(int i, int j) { return rmq(1, 0, n-1, i, j); }
};

int maxi(int a, int b) { if (a > b) return a; return b; }

int main() {
	int N, C, c, p, q, diff;
	int T;
	cin >> T;
	for(int t=0; t<T; t++) {
		cin >> N >> C;
		vector<int> A(N);	
		A.assign(N, 0);
		SumSegmentTree segmentTree(&A);
		for(int w=0; w<C; w++) {
			cin >> c >> p >> q;
			p--; q--;
			if(c==0) {
				cin >> diff;
				segmentTree.update(p, q, diff);
				// segmentTree.print();
			} else {
				int sum = segmentTree.Rmq(p, q);
				cout << sum << endl;
			}
		}
	}
	return 0;
}