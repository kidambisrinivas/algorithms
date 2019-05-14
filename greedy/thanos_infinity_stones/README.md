
# Custom Problem Set - Thanos Inifinity Stones

* [Problem link](problem.pdf): problem.pdf in same folder
* Dataset links
	* [input1.txt](https://gist.githubusercontent.com/kidambisrinivas/387a5dc4bc2e27f0afade8a8cce14c51/raw/4cd757b53f817c67e5c7fd45264d5d8e00d84437/thanos_infinity_stones_input1.txt), [output1.txt](https://gist.githubusercontent.com/kidambisrinivas/b062c48f4711655be03fe6956dae31b1/raw/67f23eb0b5db9d427f38b8278f5f7c538fdf9543/thanos_infinity_stones_output1.txt)
	* [input2.txt](https://gist.githubusercontent.com/kidambisrinivas/c50803c76dabeef46d58e96449f9cf7e/raw/f801c245cd56030bcfa2bdc1db3caedfc4d16e2b/thanos_infinity_stones_input2.txt), [output2.txt](https://gist.githubusercontent.com/kidambisrinivas/f1d42dd6379db0da158c72b8ae81b1d0/raw/4af970d811e17254a1ce511f139fe6c3c99ee6c5/thanos_infinity_stones_output2.txt)
	* [input3.txt](https://gist.githubusercontent.com/kidambisrinivas/4ac441c994670dd11a863371c352fbd4/raw/137edf518de5c8966faef0d990752799b7c5b350/thanos_infinity_stones_input3.txt), [output3.txt](https://gist.githubusercontent.com/kidambisrinivas/0d0524f592dd80dc24d1fe8897977b47/raw/697ec0d6b4f335e4aacb0d9b3263fd7f28be4ab6/thanos_infinity_stones_output3.txt)
	* [input4.txt](https://gist.githubusercontent.com/kidambisrinivas/ea0d9573ea65108f43811188fd7c7ffc/raw/56b8a25939b45fc4f7a25adf24241fd82be92744/thanos_infinity_stones_input4.txt), [output4.txt](https://gist.githubusercontent.com/kidambisrinivas/61d183e2328dfb988eea0b84c927f2bd/raw/43585c02954a65dc45de456027a97d71965da32d/thanos_infinity_stones_output4.txt)
	* [input5.txt](https://gist.githubusercontent.com/kidambisrinivas/6960663cc578edba59abcbd39095d9f3/raw/1cf38e950b1190d6e1080dcc241cf5cc071697ae/thanos_infinity_stones_input5.txt), [output5.txt](https://gist.githubusercontent.com/kidambisrinivas/43f5e6ced25475935dabc6d4c2fd0e9a/raw/c583b4a02b06becd2945b174bc9e5c62c5681f07/thanos_infinity_stones_output5.txt)
	* [input6.txt](https://gist.githubusercontent.com/kidambisrinivas/8a1b2b08853ce4fa896625127fac3482/raw/2271df7eda7e7397f9465e279aeaee696218747d/thanos_infinity_stones_input6.txt), [output6.txt](https://gist.githubusercontent.com/kidambisrinivas/261cce08cf5c7f6991cb1f134b411e67/raw/0dbbad58828be9eec9a783a19df39463dde5c40f/thanos_infinity_stones_output6.txt)
	* [input7.txt](https://gist.githubusercontent.com/kidambisrinivas/ce69c2eacc4c02d572985ff8086ec38d/raw/ee39479b6222f914ea4925573bbd2f46ac2263dd/thanos_infinity_stones_input7.txt), [output7.txt](https://gist.githubusercontent.com/kidambisrinivas/c3c951e9a9bf19a13263fec5282bfb49/raw/eb79d0c9c8648e8b5a4444ccdfc3267ac4a1b527/thanos_infinity_stones_output7.txt)
	* [input8.txt](https://gist.githubusercontent.com/kidambisrinivas/24b26667ab63d71d2b763ca5d24476d1/raw/9dd1ef8643da6b2f73b4ca2c08245b366adc118a/thanos_infinity_stones_input8.txt), [output8.txt](https://gist.githubusercontent.com/kidambisrinivas/06cd44375e7bee1c2f631f536895917b/raw/4835c2d1fc9e1326973641af5570a7afd851c4f6/thanos_infinity_stones_output8.txt)
	* [input9.txt](https://gist.githubusercontent.com/kidambisrinivas/2e72b52a7231a8fe7512f3149319e8ab/raw/251eebad48be300bac5f526a7a017e17e895d466/thanos_infinity_stones_input9.txt), [output9.txt](https://gist.githubusercontent.com/kidambisrinivas/dd4eaf9f5da3459cf88bbcb250c7755b/raw/ea1806a991314c72f964b7960e5677df13b4c25b/thanos_infinity_stones_output9.txt)
	* [input10.txt](https://gist.githubusercontent.com/kidambisrinivas/92337e8af2f22493975aee8053250b9d/raw/f7a58e96983e9bda493cb26af671ad8a5c5e032f/thanos_infinity_stones_input10.txt), [output10.txt](https://gist.githubusercontent.com/kidambisrinivas/869c7b47a2bbf5284fcd77c339c77209/raw/3a9b7abbbc4e089126562fb7a519fd3e92606ee9/thanos_infinity_stones_output10.txt)

## Solution

* Key Idea
	* Solution is Maximum Spanning Tree of the graph of planets where edge weights are time taken to travel b/w planets
	* Use prims algorithm to compute Maximum Spanning Tree [At every step, instead of computing next minimum edge in cut, fetch next maximum edge in cut]

Reference: [Prims Minimum Spanning Tree](https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/)

### Algorithm

* Maintain a parent array to store MST, key array to store incoming edge with maximum weight to a node and mstSet array to store if a node has been added to MST or not
* While mstSet doesn’t include all vertices
	* Pick a vertex u which is not there in mstSet and has minimum key value
	* Include u to mstSet
	* Update key value of all adjacent vertices of u. To update the key values, iterate through all adjacent vertices. For every adjacent vertex v, if weight of edge u-v is less than the previous key value of v, update the key value as weight of u-v
* The idea of using key values is to pick the maximum weight edge from cut. The key values are used only for vertices which are not yet included in MST, the key value for these vertices indicate the maximum weight edges connecting them to the set of vertices included in MST

## Complexity

* V - Number of planets (Number of vertices in graph)
* E - Possible routes that allows Thanos to reach any other planet from the planet that he is currently in (Number of edges in graph)

### Space Complexity

* **parent**: O(V)
* **key**: O(V)
* **mstSet**: O(V)
* **adjacencyList**: O(V + E)

* **Total**: O(4V + E)

### Run Complexity 

* **Find next min/max edge in cut**: O(V^2)
* **Update key value of non-MST tree neighbours**: O(V + E)

* **Total**: O(V + E + V^2) = O(V^2)

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

