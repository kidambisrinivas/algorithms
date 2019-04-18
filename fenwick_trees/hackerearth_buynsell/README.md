
# Hackerearth - Buy N Sell Solution

* [Problem link](https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/buy-and-sell/activity/)
* More datasets: Submit solution in hackerearth to get access to more datasets

## Solution

**Key Idea:** Binary Indexed Trees are good in finding prefix sum. Model this problem such that we just have to find prefix sum of products with price greater than target price (reverse sort products by price, store stocks of those products and compute prefix sum from 0 to i (last product with price greater than target price))

* Keep a map of product name to index, Sort products by prices in descending order and track new indexes, keep track of stock in separate array by new sorted index
* Build Fenwick tree/Binary indexed tree on stocks array [sorted in descending order of price]
* For each query, find first product with price less than query price [index i] using binary search O(logN) and calculate sum from 0 to i using Binary Indexed Tree/Fenwick tree

## Space complexity

* Map of item names to indexes: O(N)
* Array of sorted prices: O(N)
* Array of item stocks reverse sorted by prices: O(N)
* Array of index mappings (new to old after sorting): O(N)
* Array of index mappings (old to new after sorting): O(N)
* Total space complexity: O(5N)

## Run comlexity

* Sorting items by prices: O(N logN)
* Constructing BITree on item stocks array (reverse sorted by prices): O(N logN)
* Update BITree: O(logN)
* Find first item with price less than target price: O(logN)
* GetSum of all items stocks with price greater than stock price: O(logN)
* Total: 2 * O(N logN) + 2 * O(log N) = O(N * logN)


