#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <cmath>

using namespace std;

struct Tuple {
	long long int sum;
	int minIndex, maxIndex;
	Tuple() {
		sum = 0;
		minIndex = -1;
		maxIndex = -1;
	}
	Tuple(long long int a, int mi, int maxi) {
		sum = a;
		minIndex = mi;
		maxIndex = maxi;
	}
};

class SegmentTree {
private:
	vector<long long int> stSum;
	vector<int> stMin, stMax;
	vector<int> *A;
	int n, stSize;

	// O(n)
	void build(int p, int L, int R) {
		// as L == R, either one is fine
		if(L == R) {
			stSum[p] = (*A)[L];	// store the index
			stMin[p] = L;
			stMax[p] = L;
		} else {
			// recursively compute the values
			int mid = (L+R)/2;
			int left = Left(p), right = Right(p);
			build(left, L, mid);
			build(right, mid+1, R);

			stSum[p] = stSum[left] + stSum[right];
			int i1 = stMin[left], i2 = stMin[right];
			stMin[p] = (A->at(i1) < A->at(i2)) ? i1 : i2;
			i1 = stMax[left]; i2 = stMax[right];
			stMax[p] = (A->at(i2) > A->at(i1)) ? i2 : i1;
		}
	}

	void updateRmq(int p, int L, int R, int i, int diff) {
		// Base Case: If the input index lies outside the range of this segment
		if(i < L || i > R) return;		// current segment outside query range
		if(L == R) {
			if(L == i) {
				stSum[p] = stSum[p] + diff;
				int oldVal = (*A)[L];
				if(oldVal == -diff) {
					(*A)[L] = INT_MIN;
				} else if(oldVal == INT_MIN) {
					(*A)[L] = diff;
				} else {
					(*A)[L] = oldVal + diff;
				}
			}
			return;
		}

		// If the input index is in range of this node, then update
		// the value of the node and its children
		int mid = (L+R)/2;
		int left = Left(p), right = Right(p);
		updateRmq(left, L, mid, i, diff);
		updateRmq(right, mid+1, R, i, diff);

		stSum[p] = stSum[left] + stSum[right];
		int i1 = stMin[left], i2 = stMin[right];
		if((*A)[i1] == INT_MIN) {
			stMin[p] = i2;
		} else if((*A)[i2] == INT_MIN) {
			stMin[p] = i1;
		} else {
			stMin[p] = (A->at(i1) < A->at(i2)) ? i1 : i2;
		}
		i1 = stMax[left]; i2 = stMax[right];
		if((*A)[i1] == INT_MIN) {
			stMax[p] = i2;
		} else if((*A)[i2] == INT_MIN) {
			stMax[p] = i1;
		} else {
			stMax[p] = (A->at(i2) > A->at(i1)) ? i2 : i1;
		}
	}

	// O(log n)
	Tuple rmq(int p, int L, int R, int i, int j) {
		if(i > R || j < L) return Tuple(-1, -1, -1);		// current segment outside query range
		if(i <= L && R <= j) return Tuple(stSum[p], stMin[p], stMax[p]);	// inside query range

		// compute the max position in the left and right part of the interval
		int mid = (L+R)/2;
		int left = Left(p), right = Right(p);
		Tuple p1 = rmq(left, L, mid, i, j);
		Tuple p2 = rmq(right, mid+1, R, i, j);

		// if we try to access segment outside query
		if(p1.minIndex == -1 || A->at(p1.minIndex) == INT_MIN) return p2;
		if(p2.minIndex == -1 || A->at(p2.minIndex) == INT_MIN) return p1;

		long long int newSum = p1.sum + p2.sum;
		int newMinIndex = ((*A)[p1.minIndex] < (*A)[p2.minIndex]) ? p1.minIndex : p2.minIndex;
		int newMaxIndex = ((*A)[p2.maxIndex] > (*A)[p1.maxIndex]) ? p2.maxIndex : p1.maxIndex;
		return Tuple(newSum, newMinIndex, newMaxIndex);
	}
public:
	int Left(int p) { return p << 1; }
	int Right(int p) { return (p << 1) + 1; }

	SegmentTree(vector<int> *_A) {
		A = _A; n = (int)A->size();
		stSize = int(pow(2,ceil(log2(double(2*n)))));
		stSum.assign(stSize, 0);
		stMin.assign(stSize, 0);
		stMax.assign(stSize, 0);
		build(1, 0, n-1);
	}

	void print() {
		for(int x=0; x<stSum.size(); x++) {
			cout << "Index: " << x << ", Sum: " << stSum[x] << ", Min: " << A->at(stMin[x]) << ", Max: " << A->at(stMax[x]) << endl; 
		}
		for(int x=0; x<A->size(); x++) 
			cout << A->at(x) << " ";
		cout << endl;
	}

	void Update(int i, int diff) {
		updateRmq(1, 0, n-1, i, diff);
	}

	Tuple Rmq(int i, int j) { return rmq(1, 0, n-1, i, j); }
};

int main() {
	int N, Q, Ai, K, maxKTillNow = 1;
	vector<int> A;
	long long int sum[100001];
	cin >> N >> Q;
	for(int i=0; i<N; i++) {
		cin >> Ai;
		A.push_back(Ai);
		sum[i] = -1;
	}
	SegmentTree tree(&A);
	Tuple t = tree.Rmq(0, N-1);
	sum[0] = t.sum;
	for(int i=0; i<Q; i++) {
		cin >> K;
		if(sum[K] != -1) {
			cout << sum[K] << endl;
			continue;
		}
		for(int j=maxKTillNow; j<=K; j++) {
			Tuple t = tree.Rmq(0, N-1);
			int minIndex = t.minIndex, maxIndex = t.maxIndex;
			int maxMinDiff = A[maxIndex] - A[minIndex];
			tree.Update(minIndex, -A[minIndex]); // Delete max index
			tree.Update(maxIndex, -A[maxIndex]); // Delete min index
			// tree.print();
			tree.Update(minIndex, maxMinDiff); // Add diff b/w min and max
			// tree.print();
			t = tree.Rmq(0, N-1);
			sum[maxKTillNow] = t.sum;
			maxKTillNow++;
		}
		cout << sum[K] << endl;
	}
	return 0;
}