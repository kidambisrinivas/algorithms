// Problem link: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/buy-and-sell/activity/
// Solution:
// 1. Keep a map of product name to index, Sort products by prices in descending order and track new indexes, keep track of stock in separate array by new sorted index
// 2. Build Fenwick tree/Binary indexed tree on stocks array [sorted in descending order of price]
// 3. For each query, find first product with price less than query price [index i] using binary search O(logN) and calculate sum from 0 to i using Binary Indexed Tree/Fenwick tree

#include <iostream>
#include <numeric>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

/*         n --> No. of elements present in input array.  
    BITree[0..n] --> Array that represents Binary Indexed Tree. 
    arr[0..n-1] --> Input array for which prefix sum is evaluated. */

// Returns sum of arr[0..index]. This function assumes 
// that the array is preprocessed and partial sums of 
// array elements are stored in BITree[].
int getSum(int BITree[], int index) {
	int sum = 0; // Iniialize result 
	index = index + 1; // index in BITree[] is 1 more than the index in arr[] 
	// Traverse ancestors of BITree[index
	while(index > 0) {
		sum = sum + BITree[index]; // Add current element of BITree to sum
		index = index - (index & (-index)); // Move index to parent node in getSum View
	}
	return sum;
}

// Updates a node in Binary Index Tree (BITree) at given index 
// in BITree. The given value 'val' is added to BITree[i] and  
// all of its ancestors in tree. 
void updateBIT(int BITree[], int n, int index, int diff) {
	// index in BITree[] is 1 more than the index in arr[]
	index = index + 1;
	// Traverse all ancestors and add 'val'
	while(index <= n) {
		BITree[index] += diff;
		index = index + (index & (-index)); // Update index to that of parent in update View 
	}
}

// Constructs and returns a Binary Indexed Tree for given 
// array of size n
int *constructBITree(int arr[], int n, bool build) {
	// Create and initialize BITree[] as 0
	int *BITree = new int[n+1];
	for (int i=1; i<=n; i++) 
        BITree[i] = 0;
    if(build)
    	for(int i=0; i<n; i++)
    		updateBIT(BITree, n, i, arr[i]);
    return BITree;
}

void PrintBITree(int BITree[], int n) {
	for (int i=1; i<=n; i++)
		cout << BITree[i] << " ";
	cout << endl;
}

// Find first item less than or equal to target in an array sorted in descending order
// Returns index of first item less than or equal to target or n if whole array greater than target
int firstLessThanBinarySearch(int arr[], int n, int target) {
	int s = 0, e = n-1;
	int firstIndexLessThanTarget = n;
	while(s <= e) {
		int mid = (s + e) / 2;
		if(arr[mid] <= target && (mid == 0 || arr[mid-1] > target)) {
			firstIndexLessThanTarget = mid;
			break;
		}
		if(s == e) break;
		if(arr[mid] > target) {
			s = mid+1;
		} else if(arr[mid] <= target) {
			e = mid;
		}
	}
	return firstIndexLessThanTarget;
}

// Driver function to sort the vector elements 
// by second element of pairs 
bool sortbydesc(const pair<int,int> &a, 
              const pair<int,int> &b) 
{ 
    return (a.first > b.first); 
} 

// Function to sort character array b[] 
// according to the order defined by a[] 
int* pairsort(int a[], int n) 
{ 
	int *idx = new int[n];
  	iota(idx, idx+n, 0);
    pair<int, int> pairt[n]; 
  
    // Storing the respective array 
    // elements in pairs. 
    for (int i = 0; i < n; i++)  
    { 
        pairt[i].first = a[i]; 
        pairt[i].second = idx[i]; 
    } 
  
    // Sorting the pair array. 
    sort(pairt, pairt + n, sortbydesc); 
      
    // Modifying original arrays 
    for (int i = 0; i < n; i++)  
    { 
        a[i] = pairt[i].first; 
        idx[i] = pairt[i].second; 
        // cout << a[i] << " " << idx[i] << "\n";
    } 
    return idx;
}

void PrintMap(map<string, int> m, int ridx[], int itemPrices[], int itemStocks[]) {
	map<string, int>::iterator itr;
	for (itr = m.begin(); itr != m.end(); ++itr) { 
        cout << itr->first << ": " << ridx[itr->second] << ", price: " << itemPrices[ridx[itr->second]] << ", stock: " << itemStocks[ridx[itr->second]] << '\n'; 
    } 
}

int main() {
	map<string, int> itemIndexes;
	int itemPrices[100001], itemStocks[100001];
	int N, Q, ki, minPrice;
	string Xi;
	string cmd, itemName;
	cin >> N;
	for(int i=0; i<N; i++) {
		cin >> Xi >> ki;
		pair<string, int> p;
		p.first = Xi; p.second = i;
		itemIndexes.insert(p);
		itemPrices[i] = ki;
		itemStocks[i] = 0;
		// cout << Xi << " " << ki << "\n";
	}
	int *idx = pairsort(itemPrices, N);
	int *ridx = new int[N];
	for(int i=0; i<N; i++)
		ridx[idx[i]] = i;
	int *BITree = constructBITree(itemStocks, N, false);
	cin >> Q;
	//for(int i=0; i<N; i++)
	//	cout << "prices: " << itemPrices[i] << ", item: " << idx[i] << "\n";
	for(int i=0; i<Q; i++) {
		cin >> cmd;
		if(cmd == "+") {
			cin >> itemName;
			int index = ridx[itemIndexes.find(itemName)->second];
			itemStocks[index]++;
			updateBIT(BITree, N, index, 1);
		} else if(cmd == "-") {
			cin >> itemName;
			int index = ridx[itemIndexes.find(itemName)->second];
			if(itemStocks[index] > 0) {
				itemStocks[index]--;
				updateBIT(BITree, N, index, -1);
			}
		} else if(cmd == "?") {
			// PrintMap(itemIndexes, ridx, itemPrices, itemStocks); cout << endl;
			cin >> minPrice;
			int firstIndexLessThanEqualTarget = firstLessThanBinarySearch(itemPrices, N, minPrice);
			int firstIndexMoreThanTarget = firstIndexLessThanEqualTarget - 1;
			// cout << "minPrice: " << minPrice << ", firstIndexMoreThanTarget: " << firstIndexMoreThanTarget << " ";
			if(firstIndexMoreThanTarget == -1)
				cout << 0 <<  "\n";
			else
				cout << getSum(BITree, firstIndexMoreThanTarget) << "\n";
		}
	}
	return 0;
}