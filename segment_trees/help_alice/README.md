
# Custom Problem Set - Help Alice Solution

* [Problem link](problem.pdf): problem.pdf in same folder
* Dataset links
	* [input1.txt](https://gist.githubusercontent.com/kidambisrinivas/58de10aba13e0059507ecefc8d19fa16/raw/0efd7da85dd6f7ea34478e13da303ccc5cc9625c/rangesum_input1.txt), [output1.txt](https://gist.githubusercontent.com/kidambisrinivas/78b4f007848e1d3fe37c3ea2e1e3f42e/raw/ec91da7c8fda1b5db1dddf4ae31bf944bfbf4cd5/rangesum_output1.txt)
	* [input2.txt](https://gist.githubusercontent.com/kidambisrinivas/d01c6132aacfaab00700fc1dbebbfb85/raw/935f36fa0f00c8961fe0014316fbde43270ca14e/rangesum_input2.txt), [output2.txt](https://gist.githubusercontent.com/kidambisrinivas/115f38b807895f7ff5e9a0117c3ce94f/raw/80c5dfb247bdfc1ef849e6ef2f3410ee518ec0ce/rangesum_output2.txt)
	* [input3.txt](https://gist.githubusercontent.com/kidambisrinivas/2aae9c42b07909459ff4e57bb9ae74ef/raw/a911245dcf48e0897cc1eb955f000c9d1c1c6b59/rangesum_input3.txt), [output3.txt](https://gist.githubusercontent.com/kidambisrinivas/178aed8fc206f8b36994017335673a24/raw/d1ac9718092ac1518cc60c7f9a6854431ed6458f/rangesum_output3.txt)
	* [input4.txt](https://gist.githubusercontent.com/kidambisrinivas/a69b6a722d32295a163c36413bd67891/raw/311461ab82d62a695ca197c288bb80ef4eb5150f/rangesum_input4.txt), [output4.txt](https://gist.githubusercontent.com/kidambisrinivas/72d665960f7c254946c7e13abd68ed9f/raw/291c52d1256528b0d0337ae85b181d788d83dbcf/rangesum_output4.txt)
	* [input5.txt](https://gist.githubusercontent.com/kidambisrinivas/40c37aa0b065c090a7d2944a43e3c1e3/raw/35db677d1ee2e3b35c2d7ca4715a3d4a497200db/rangesum_input5.txt), [output5.txt](https://gist.githubusercontent.com/kidambisrinivas/2f2fc8ba3679bdfd42335dc690fd43ab/raw/aa95370227c8ddadbd162a3d9838a5a3358cab2e/rangesum_output5.txt)

## Solution

* Build a sum segment tree to store number of odd numbers in every range
* For every update to index i
	* if oldval is odd and newval is even, set diff to -1
	* if oldval is even and newval is odd, set diff to 1
	* else, set diff to 0
	* Update the sum-value of all nodes with range [L, R] in segment tree where `L <= i <= R` with +diff

## Complexity

* N - Number of numbers in array

### Space Complexity

* **Space Complexity:** O(5N) (~ for segmentTree(2^ceil(log2(2N))))

### Run Complexity

* **Query Complexity:** O(logN) per query

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

