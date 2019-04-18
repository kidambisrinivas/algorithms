
# UVA 12238 - Ants Colony Solution

* [Problem link](https://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3390)
* [More datasets](https://www.udebug.com/UVa/12238)

## Solution

* **Key Idea:** Since each ant hill is connected is only one of previous ant hills, ant hill network is a tree

* Build an Euler Tour Representation of ant hills [E[], L[], H[]]
* Build a MIN segment tree on levels array L[] to give min_index of node with minimum level between first occurence of 2 nodes in Euler tour array E[]
* Shortest path between 2 ant hills is computed as Dist(A, LCA(A, B)) + Dist(B, LCA(A, B))
* To efficiently compute Distance between a node A and its LCA(A, B) with B, store distance of every node from root of anthills tree

## Space complexity

* Weighted Lowest Common Ancestor / Range Minimum Query
* Input: Tree with edge weights
* Output: LCA of 2 nodes in tree and shortest distance b/w 2 nodes
* Space complexity: O(3 * (2N-1)) + O(3 * N) + O(2 * (2N-1)-1) = O(6N-3 + 3N + 4N-3) = O(13N - 6)

## Run complexity

* Build: EulerTour: O(2N-1), SegmentTreeBuild: O(4N-2)
* LCA Query: O(log(2N-1))
* Overall: O(6N-3 + log(2N-1)) = O(N + log(N)) = O(N)


