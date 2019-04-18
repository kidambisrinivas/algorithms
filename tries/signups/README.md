
# Custom Problem Set - Signup Registration System Solution

* [Problem link](problem.pdf): problem.pdf in same folder
* Dataset links
	* [input1.txt](https://gist.githubusercontent.com/kidambisrinivas/2fa5c5312de4e27c78ed1aa584b7280a/raw/ed0e97f9ff5648898df392517f0cbf447d3a2878/signup_input1.txt), [output1.txt](https://gist.githubusercontent.com/kidambisrinivas/bdd798ae1260d1182c79dbf4325f169b/raw/a9f0f70d4482cb18ca12f665e52e733b18d054b5/signup_output1.txt)
	* [input2.txt](https://gist.githubusercontent.com/kidambisrinivas/039fd8b3949e3c91e8bb2f72d490db7b/raw/d52ee5f1012161b9498f6ca0272a865faff9f25b/signup_input2.txt), [output2.txt](https://gist.githubusercontent.com/kidambisrinivas/49244bb6eb79ed0fa88eedfd3e7d59e0/raw/f1926647e446475dc7e09891b182d81742f98c47/signup_output2.txt)
	* [input3.txt](https://gist.githubusercontent.com/kidambisrinivas/5d48243f4d56a954419662b41ba6326d/raw/604548369b729249ba4893034d4ef499a1c30153/signup_input3.txt), [output3.txt](https://gist.githubusercontent.com/kidambisrinivas/f91614cec3187d00532907db1ea4cb7e/raw/fbb26f56a38d0f355cfe786c47555ce99be7ffc3/signup_output3.txt)
	* [input4.txt](https://gist.githubusercontent.com/kidambisrinivas/6305e0e5ff28fb1009b372534ecafe84/raw/ff44cadf3fb272b173225605cef47b4ee058cae2/signup_input4.txt), [output4.txt](https://gist.githubusercontent.com/kidambisrinivas/8c270d773e5db4decd48bcc502125971/raw/a9fc9a9fc2324070ccd23c0eef57dde13914c2c6/signup_output4.txt)
	* [input5.txt](https://gist.githubusercontent.com/kidambisrinivas/16df2ccc8225294250a8a27655ad28dd/raw/1dce5e3df708c05651ccdc570ec80b9921b2d2af/signup_input5.txt), [output5.txt](https://gist.githubusercontent.com/kidambisrinivas/aed885040dbd1e71bdc4b60292bea0ef/raw/9870663626d890e38e62add112035aff3bdf9d3f/signup_output5.txt)
	* [input6.txt](https://gist.githubusercontent.com/kidambisrinivas/289ab7fa26a13175f3cadfd930408fe2/raw/6b365277abd5822e2e390dc795ed6e1975fbe19c/signup_input6.txt), [output6.txt](https://gist.githubusercontent.com/kidambisrinivas/1496272fa893516f54598b8819e47f7b/raw/e4cf80aa05729e767d97de1b547982e82e69ee4e/signup_output6.txt)
	* [input7.txt](https://gist.githubusercontent.com/kidambisrinivas/b4693682f89bd3db59e2086a1c8f8399/raw/c001b272d69b3bc4db343582dc650ab07e4707d4/signup_input7.txt), [output7.txt](https://gist.githubusercontent.com/kidambisrinivas/40adcfe45c7283c0d08305fa8e58741c/raw/d0ea8a727c76f889939cc05e1bae61fbedcb44fa/signup_output7.txt)
	* [input8.txt](https://gist.githubusercontent.com/kidambisrinivas/48598f7e09a7a8d204e183558e7c0cf2/raw/621ee197997e2d29ee748454f803095a020cf924/signup_input8.txt), [output8.txt](https://gist.githubusercontent.com/kidambisrinivas/e38d80febb041550894531d62ceff67f/raw/839c6f940ececef41b0c43b8daffb47906d13cd1/signup_output8.txt)


## Solution

* Build a trie on 36 characters letter-set [26 alphabets and 10 digits]
* Every word in dictionary and query has to be comprised of only these characters
* For every new signup
	* If user_id not found in Trie, add the user_id
	* Else if found, find the first whole number 0,1,..9,10,11,..21,..., which is present in trie
* To convert the number to string, use the optimized number conversion function [Otherwise you might get a TLE]

**Max string length of user_id:** L
**Number of users:** N 
**Space Complexity:** O(ALPHABET_SIZE * L * N)
**Insert and search complexity:** O(L)

## Testcases

Once you download all the above testcases into a testcases folder like below

**Source code folder**

```
➜  signups ls -ltrh
total 112
-rw-r--r--@  1 srinivas  staff    19K Apr 15 12:45 problem.pdf
-rw-r--r--@  1 srinivas  staff   2.6K Apr 15 13:01 main.cpp
-rwxr-xr-x   1 srinivas  staff    27K Apr 16 11:00 a.out
-rw-r--r--@  1 srinivas  staff   1.4K Apr 16 12:21 README.md
drwxr-xr-x  17 srinivas  staff   544B Apr 16 12:44 testcases/
```

**Testcases folder**

```
➜  signups ls -ltrh testcases
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