
# Custom Problem Set - Help Alice Solution

* [Problem link](problem.pdf): problem.pdf in same folder
* Dataset links
	* [input1.txt](https://gist.githubusercontent.com/kidambisrinivas/f3a5a82aa9c62eed4d36ffbdab3ac670/raw/83030c0e7e00d67a96528c2d5ea973b5d4849293/newyork_input1.txt), [output1.txt](https://gist.githubusercontent.com/kidambisrinivas/d8dc2fb43ee8c26cb49080ead6bf40bb/raw/81dfdd223eb6a23ef9d4bc3457c3c8dcdcba76cf/newyork_output1.txt)
	* [input2.txt](https://gist.githubusercontent.com/kidambisrinivas/8d352b840c972fd273a843f35806440f/raw/c7d41bc7c0de7a4dced69883028940c4b1985e75/newyork_input2.txt), [output2.txt](https://gist.githubusercontent.com/kidambisrinivas/83db8c6a00d76d1ad687decc1c72c352/raw/be3e90f89fa59f81af9de5c472b9bae9d9321ef9/newyork_output2.txt)
	* [input3.txt](https://gist.githubusercontent.com/kidambisrinivas/68c19e8598a52b25df69ac46e2824878/raw/ea8b0a2947da061671fb18952b232a348bcbc841/newyork_input3.txt), [output3.txt](https://gist.githubusercontent.com/kidambisrinivas/6c932253c4a878750ddb8610ac1bc669/raw/a662241216c530621c906d3683d53222beed723e/newyork_output3.txt)
	* [input4.txt](https://gist.githubusercontent.com/kidambisrinivas/aff2c6997150015395028e23a57da5cf/raw/c31149962f23ded9f72f10327702f4501184c826/newyork_input4.txt), [output4.txt](https://gist.githubusercontent.com/kidambisrinivas/d51df4adaeb82cef8e66667879528668/raw/0360d25aec733b28de981a9e88d116b99f80004e/newyork_output4.txt)

## Solution

* Key Idea
	* Build the segment tree bottom up and use node pointer based implementation
	* Segment tree is built on cartesian coordinate range and not on array indexes as usual
	* Ranges lengths are not uniform, so for every node, store left, right and mid [Dynamic ranges]
	* Segment tree update and search cost will be O(logN) where N is number of buildings

### Algorithm

* Add both the endpoints of all buildings to a MIN priority queue / heap: O(N logN)
* GetLeaves: Each segment tree leaf will be built from 2 of these endpoints in sorted order as left -> e1, right -> e2, mid -> -1 [No mid]
* BuildTree: Each internal node of segment tree will be built from 2 nodes in next level as left -> leftChild->left, right -> rightChild->right, mid -> leftChild -> right [Mid will be leftChild->right]
* AddBuildings: 
	* Iterate through all buildings
	* For every segment tree node of the current building, compute overlapCost
		* If current building is first building in node range, then update height and add node length as overlapCost (first building)
		* Else If current building's height is greater than any previous building in current node's range, then update height and add node length as overlapCost (taller building in current range)
		* Else, Dont do anything
	* Sum all overlapCosts and print solution


**Numer of buildings:** N
**Numer of endpoints:** 2N
**Space Complexity:** O(10N) (~ for segmentTree(2^ceil(log2(4N)))) + O(2N) for priority queue = O(12N)
**AddBuilding Complexity:** O(log 4N) per query
**Total Complexity:** (4N) * O(log 4N) [To add N buildings to Segment Tree and compute overlap cost]

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

