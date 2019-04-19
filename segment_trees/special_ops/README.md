
# Custom Problem Set - CS Special OPs Solution

* [Problem link](problem.pdf): problem.pdf in same folder
* Dataset links
	* [input1.txt](https://gist.githubusercontent.com/kidambisrinivas/80126a7347e59c57c43cd11d9e0dfb20/raw/14e440bc957647b8baa0c8dab277fc8f77f51dfc/specialops_input1.txt), [output1.txt](https://gist.githubusercontent.com/kidambisrinivas/0ca62d3a73fa8afc248f3e8e36735ff6/raw/2fbf7c89cd5ce106a95a01a56163601548477235/specialops_output1.txt)
	* [input2.txt](https://gist.githubusercontent.com/kidambisrinivas/13d98c660e495c6a349a1bc836643c20/raw/232fe4519548036168dfdde114d7b19c2134c459/specialops_input2.txt), [output2.txt](https://gist.githubusercontent.com/kidambisrinivas/95a1652309f7e424d637f92a28bdaf84/raw/86f4b56115f5e9de47591a71b87812253a51fbe1/specialops_output2.txt)
	* [input3.txt](https://gist.githubusercontent.com/kidambisrinivas/fbda5673549238dac9c9bb976e952139/raw/c3089c27eb04eb02e69ffb8c3c0373b74f583c5f/specialops_input3.txt), [output3.txt](https://gist.githubusercontent.com/kidambisrinivas/fe2bd7a0c7b3560e655b15737193156f/raw/ddc544efada91cd34b186c60543f4fc58c043313/specialops_output3.txt)
	* [input4.txt](https://gist.githubusercontent.com/kidambisrinivas/3a6cbc48a500c98e059fc5cd9d558dcf/raw/437cb05c4219bf4885e8fceacfab3f6cc9ceb505/specialops_input4.txt), [output4.txt](https://gist.githubusercontent.com/kidambisrinivas/156fc2e18b1b8ee6c4f7fbe7090160f2/raw/59297778c2be3a3b110ddf518c82f8a9824db9fb/specialops_output4.txt)
	* [input5.txt](https://gist.githubusercontent.com/kidambisrinivas/b0c5bb7e7cc18dc108130fe8bae6cc27/raw/feb547c85e727546b32db5b049874b6bf7900b81/specialops_input5.txt), [output5.txt](https://gist.githubusercontent.com/kidambisrinivas/2f2fc8ba3679bdfd42335dc690fd43ab/raw/aa95370227c8ddadbd162a3d9838a5a3358cab2e/rangesum_output5.txt)
	* [input6.txt](https://gist.githubusercontent.com/kidambisrinivas/27e37e80c3b6fce237578dbfb103dfa0/raw/c79192059959885f5814fb300b9986af6a8a1fec/specialops_input6.txt), [output6.txt](https://gist.githubusercontent.com/kidambisrinivas/bf2b496c574155c0d5b3b33c75076d0a/raw/5227d6bf679896bcd0757f8c83e7cff813d34e29/specialops_output6.txt)
	* [input7.txt](https://gist.githubusercontent.com/kidambisrinivas/18063f144c96dd25b4b9b81de28b1080/raw/67a6e98ee102996b9638352923e09fe09535aa6a/specialops_input7.txt), [output7.txt](https://gist.githubusercontent.com/kidambisrinivas/60356699f10cc1a36c70369b7041a474/raw/0a58e905d48b6ad091d8d4be03fbad8baf982875/specialops_output7.txt)

## Solution

* Build a segment tree which stores sum, min_index (index of smallest item), max_index in every range
* For every op k,
	* Find min_index and max_index in range [0, N-1]
	* Find diff as A[max_index] - A[min_index]
	* Delete items at min_index and max_index by setting items to INT_MIN
		* To remove min_index from segment_tree, subtract sum by -A[min_index] for every node with L <= min_index <= R
		* To remove max_index from segment_tree, subtract sum by -A[max_index] for every node with L <= max_index <= R
		* For updating min_index of segment_tree nodes, for every node with L <= min_index <= R
			* if left node's min_index has INT_MIN, set min_index of current node as right index's min_index
			* if right node's min_index has INT_MIN, set min_index of current node as left index's min_index
		* For updating max_index of segment_tree nodes, for every node with L <= max_index <= R, Repeat the same procedure for max_index
	* Add diff as a new item to segment_tree at previous min_index. That way its just a segment tree update operation and not a new insert
	* Cache the results in a sum[] array for kth op
* We can only perform kth op after 0 .. k-1 ops. So if new input k is less than max k seen till now, just read the sum from cached sum[] array

## Complexity

* N - Number of numbers in array

### Space Complexity

* **Space Complexity:** O(3 * 5N) (~ for segmentTree(2^ceil(log2(2N))) contains sum, min_index and max_index)

### Run Complexity

* **1 op Complexity:** 5 * O(logN) per op
	* 2 reads, 2 deletes, 1 insert per op -> So 5 ops in total
* **K ops Complexity:** 5K * O(logN)

## Testcases

Once you download all the above testcases into a testcases folder like below

**Source code folder**

```
➜  help_alice ls -ltrh
total 112
-rw-r--r--@  1 srinivas  staff    19K Apr 15 12:45 problem.pdf
-rw-r--r--@  1 srinivas  staff   2.6K Apr 15 13:01 main.cpp
-rwxr-xr-x   1 srinivas  staff    27K Apr 16 11:00 a.out
-rw-r--r--@  1 srinivas  staff   1.4K Apr 16 12:21 README.md
drwxr-xr-x  17 srinivas  staff   544B Apr 16 12:44 testcases/
```

**Testcases folder**

```
➜  help_alice ls -ltrh testcases
total 200
-rw-r--r--@ 1 srinivas  staff    45B Apr 15 12:46 input1.txt
-rw-r--r--@ 1 srinivas  staff   189B Apr 15 12:46 input2.txt
-rw-r--r--@ 1 srinivas  staff    23B Apr 15 12:46 output2.txt
-rw-r--r--@ 1 srinivas  staff   185B Apr 15 12:46 input3.txt
-rw-r--r--@ 1 srinivas  staff    30B Apr 15 12:47 output3.txt
-rw-r--r--@ 1 srinivas  staff    54B Apr 15 12:47 input4.txt
-rw-r--r--@ 1 srinivas  staff     7B Apr 15 12:47 output4.txt
-rw-r--r--@ 1 srinivas  staff    35K Apr 15 12:47 input5.txt
-rw-r--r--@ 1 srinivas  staff   5.5K Apr 16 10:59 output5.txt
-rw-r--r--@ 1 srinivas  staff     7B Apr 16 12:45 output1.txt
...
```

Run the following command to test all testcases:

```bash
ls -1 testcases | grep input | perl -nle 'if($_ =~ /input(\d+)/) { print $1; }' | xargs -I % bash -c 'time ./a.out < testcases/input%.txt > testcases/myoutput%.txt; diff -w testcases/output%.txt testcases/myoutput%.txt' > testcases/log
```

Inspect the log to check the diff b/w your solution and correct solution [Empty log file "testcases/log" denotes success]

