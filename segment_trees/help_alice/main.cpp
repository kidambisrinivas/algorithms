#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SegmentTree {
private:
	vector<int> st, A;
	int n, stSize;

	// O(n)
	void build(int p, int L, int R) {
		// as L == R, either one is fine
		if(L == R) {
			st[p] = (A[L] % 2 == 1) ? 1 : 0;	// store the index
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

		return p1 + p2;
	}

	void updateRmq(int p, int L, int R, int i, int diff) {
		// Base Case: If the input index lies outside the range of this segment
		if(i < L || i > R) return;		// current segment outside query range
		if(L == R) {
			if(L == i) {
				st[p] = st[p] + diff;
			}
			return;
		}

		// If the input index is in range of this node, then update
		// the value of the node and its children
		int mid = (L+R)/2;
		int left = Left(p), right = Right(p);
		updateRmq(left, L, mid, i, diff);
		updateRmq(right, mid+1, R, i, diff);
		st[p] = st[left] + st[right];
	}
public:
	int Left(int p) { return p << 1; }
	int Right(int p) { return (p << 1) + 1; }

	SegmentTree(const vector<int> &_A) {
		A = _A; n = (int)A.size();
		stSize = int(pow(2,ceil(log2(double(2*n)))));
		st.assign(stSize, 0);
		build(1, 0, n-1);
	}

	void Update(int i, int newval) {
		int oldval = A[i];
		A[i] = newval;
		int diff = 0;
		if(oldval % 2 == 0 && newval % 2 == 1)
			diff = 1;
		else if(oldval % 2 == 1 && newval % 2 == 0)
			diff = -1;
		else 
			diff = 0;
		if(diff != 0)
			updateRmq(1, 0, n-1, i, diff);
	}

	int Rmq(int i, int j) { return rmq(1, 0, n-1, i, j); }
};

int main() {
	int N, Q, xi, yi, cmd;
	cin >> N;
	vector<int> A;
	for(int i=0; i<N; i++) {
		cin >> xi;
		A.push_back(xi);
	}
	cin >> Q;
	SegmentTree st(A);
	for(int j=0; j<Q; j++) {
		cin >> cmd;
		if(cmd == 0) {
			cin >> xi >> yi;
			xi--;
			A[xi] = yi;
			st.Update(xi, yi);
		} else if(cmd == 1) {
			cin >> xi >> yi;
			xi--; yi--;
			int numOdds = st.Rmq(xi, yi);
			cout << (yi-xi+1) - numOdds << endl;
		} else if(cmd == 2) {
			cin >> xi >> yi;
			xi--; yi--;
			int numOdds = st.Rmq(xi, yi);
			cout << numOdds << endl;
		}
	}
	return 0;
}