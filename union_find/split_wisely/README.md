
# Custom Problem Set - Split Wisely Solution

* [Problem link](problem.pdf): problem.pdf in same folder
* Dataset links
	* [input1.txt](https://gist.githubusercontent.com/kidambisrinivas/fb7ff7c2496a40f2b6cffb666d76d545/raw/7ffa656c24c8528c7fc9a0c0fc4f49edb898c3c7/splitwisely_input1.txt), [output1.txt](https://gist.githubusercontent.com/kidambisrinivas/6e2723e97343efe047277f85b22cc192/raw/5df8b8b0b16bec8e9b822121ad0c59b5cc04e944/splitwisely_output1.txt)
	* [input2.txt](https://gist.githubusercontent.com/kidambisrinivas/de4ccb7421a1a380dfa722708aa590a2/raw/cd99d9a6418aafbcec6ee96d16b2a7560cf4ec39/splitwisely_input2.txt), [output2.txt](https://gist.githubusercontent.com/kidambisrinivas/7a29610d1b8335dd3caaf4484cd32463/raw/7e2f287467c723d0bc15fe5e57c688f3b3c13580/splitwisely_output2.txt)
	* [input3.txt](https://gist.githubusercontent.com/kidambisrinivas/8f1dd254dfeeb06c4a1cdff7e67f39ff/raw/590135caf761db1a934b6166cd470f0e79b822a1/splitwisely_input3.txt), [output3.txt](https://gist.githubusercontent.com/kidambisrinivas/4cf7cc4fa1ca3f071bf44c43e65d5af0/raw/428e85683077364c38b4696635ef6316d3c17920/splitwisely_output3.txt)
	* [input4.txt](https://gist.githubusercontent.com/kidambisrinivas/9f0769a916391a1e403ff2e555ccf673/raw/b1c302f54d7f416deafd04be2c2811d4051438bc/splitwisely_input4.txt), [output4.txt](https://gist.githubusercontent.com/kidambisrinivas/de74975ccf58d122d414dcd302124c1c/raw/47ca9781886fabbd4924ac911c4d4619b33da077/splitwisely_output4.txt)

## Solution

* Maintain a UFDS data structure to store friends p[N], r[N]
* Another owe[N] array would store prices
* We perform a union operation for every friends op
* Finally we scan through the parents array and for every person, we check if his group's owe values sum up to 0
	* If owe values sum up to 0, we print HOUDU
	* Else, we print ILLA
* **Skip if parent set already processed**

**Note:** We've a O(N^2) loop in the solution, but we skip if a parent set has already been processed. So in effect, each person is only checked once and each person's set is only processed once.

## Complexity

* N - Number of persons

### Space Complexity

* **Space Complexity:** O(3N) [p[N], r[N], owe[N]]

### Run Complexity

* **Query Complexity (for M queries):** O(M * Ackermans(N))
	* O(M * 4) for M queries ~~ O(1) amortized time per find query
* **Total time per set:** O(N * Ackermans(N))
	* O(N * 4) To find root of every person and check if that root's set has sum of owe[] as 0

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

