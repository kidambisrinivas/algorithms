#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

class MaxSegmentTree {
private:
	vector<int> st, A;
	int n, stSize;

	// O(n)
	void build(int p, int L, int R) {
		// as L == R, either one is fine
		if(L == R) {
			st[p] = L;	// store the index
		} else {
			// recursively compute the values
			int mid = (L+R)/2;
			int left = Left(p), right = Right(p);
			build(left, L, mid);
			build(right, mid+1, R);
			int p1 = st[left], p2 = st[right];
			st[p] = (A[p2] >= A[p1]) ? p2 : p1;
		}
		// printf("st[%d]: %d\n", p, st[p]);
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

		return (A[p2] >= A[p1]) ? p2 : p1;	// as in build routine
	}
public:
	int Left(int p) { return p << 1; }
	int Right(int p) { return (p << 1) + 1; }

	MaxSegmentTree(const vector<int> &_A) {
		A = _A; n = (int)A.size();
		stSize = int(pow(2,ceil(log2(double(2*n)))));
		st.assign(stSize, 0);
		build(1, 0, n-1);
	}

	int Rmq(int i, int j) { return rmq(1, 0, n-1, i, j); }
};

int main() {
	return 0;
}