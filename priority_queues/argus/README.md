
# Custom Problem Set - Argus Solution

* [Problem link](problem.pdf): problem.pdf in same folder
* Dataset links
	* [input1.txt](https://pastebin.com/raw/UYTC6skw), [output1.txt](https://pastebin.com/raw/6D8SwsXg)
	* [input2.txt](https://pastebin.com/raw/nw3vVALi), [output2.txt](https://pastebin.com/raw/nwViUZDZ)
	* [input3.txt](https://pastebin.com/raw/w69FQweJ), [output3.txt](https://pastebin.com/raw/S6BXVxsC)
	* [input4.txt](https://pastebin.com/raw/rYqD1tF3), [output4.txt](https://pastebin.com/raw/WrEeeWH8)
	* [input5.txt](https://pastebin.com/raw/bbZG0i0m), [output5.txt](https://gist.github.com/kidambisrinivas/853619817dcbeb3ced01e8ff10589d5a)
	* [input6.txt](https://pastebin.com/raw/CrD55fvf), [output6.txt](https://gist.github.com/kidambisrinivas/1bb15f922f46528b6b5b977989d1a457)
	* [input7.txt](https://pastebin.com/raw/j7N1bfjm), [output7.txt](https://pastebin.com/raw/6D8SwsXg)

## Solution

* Store qnum, period and nexttick time for each query
* Keep a priority queue of Queries sorted based on next tick time
* To get top K queries to be executed
	* Pop a query from the priority queue
	* Update its nexttick 
	* Push back to Priority Queue

**Space Complexity:** 3 integers for storing a Query ~ O(3N)
**Query Complexity:** O(KlogN) [K - Top K queries to be executed, N - Number of queries registered]

## Testcases

Once you download all the above testcases into a testcases folder like below

**Source code folder**

```
➜  argus ls -ltrh
total 112
-rw-r--r--@  1 srinivas  staff    19K Apr 15 12:45 problem.pdf
-rw-r--r--@  1 srinivas  staff   2.6K Apr 15 13:01 main.cpp
-rwxr-xr-x   1 srinivas  staff    27K Apr 16 11:00 a.out
-rw-r--r--@  1 srinivas  staff   1.4K Apr 16 12:21 README.md
drwxr-xr-x  17 srinivas  staff   544B Apr 16 12:44 testcases/
```

**Testcases folder**

```
➜  argus ls -ltrh testcases
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