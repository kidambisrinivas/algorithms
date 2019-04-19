
# UVA 11235 - Frequent Values Solution

* [Problem link](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2176)
* [More datasets](https://www.udebug.com/UVa/11235)

## Solution

* Maintain a count array which stores counts of repeating values c[N]
* Maintain a `starting` array which stores starting index of each value s[N]
* Build segment tree on count array
* For every query (i, j), there are 2 possibilities
	* If A[i] == A[j], then simply return j - i + 1 [Length of query range as count]
	* Else, A[i] may repeat till some index k, then k to s[j] from which A[j] will start and go on till j
		* Count = Max(itemICount, segmentTree.Rmq(k, s[j]-1),itemJCount)

## Complexity

* N - Number of numbers in array

### Space Complexity

* **Space Complexity:** O(7N)
	* c[N] : O(N)
	* s[N] : O(N)
	* segmentTree : O(5N) [2^ceil(log2(2N))]

### Run Complexity

* **Query Complexity:** O(logN)


