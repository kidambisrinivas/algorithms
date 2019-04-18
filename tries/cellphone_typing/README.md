
# Custom Problem Set - Cellphone Typing Solution

* [Problem link](problem.pdf): problem.pdf in same folder
* Dataset links
	* [input1.txt](https://gist.githubusercontent.com/kidambisrinivas/42e5d133a80e489970c0e62245342244/raw/cd6d876c6cb5054dbc768863e24af8c01a9f5cbf/cellphonetyping_input1.txt), [output1.txt](https://gist.githubusercontent.com/kidambisrinivas/1c75b63b89c27a0e784e14adc1a57376/raw/d73f96bccef2221900e27d46ddc823ec8c2626c7/cellphonetyping_output1.txt)
	* [input2.txt](https://gist.githubusercontent.com/kidambisrinivas/27583c5d7bdf6061bc7a27574547d09e/raw/71f4163da815b8b36a513a83a2b207e1d9b10664/cellphonetyping_input2.txt), [output2.txt](https://gist.githubusercontent.com/kidambisrinivas/78b44ce867b68aa3730268f289fc5fa4/raw/cc4a8ccfeb3daf2fa722dcb25dbceb1ae4f488dc/cellphonetyping_output2.txt)
	* [input3.txt](https://gist.githubusercontent.com/kidambisrinivas/a5c68e8201dbfd56de69bca548b873c7/raw/05cf79eb793c27835e6f8dd3b180a7cd8ce11c19/cellphonetyping_input3.txt), [output3.txt](https://gist.githubusercontent.com/kidambisrinivas/8773c6241e719685b809188cc03ef69e/raw/597c934326b8a241a01c78dd8e87858e60437a92/cellphonetyping_output3.txt)
	* [input4.txt](https://gist.githubusercontent.com/kidambisrinivas/e5b1716a62109e35361b8ab3d98730b5/raw/83701f13362af68ac7a59d879904e2e71369641c/cellphonetyping_input4.txt), [output4.txt](https://gist.githubusercontent.com/kidambisrinivas/3a64e834929c799ae4ef19bca7bf0439/raw/6bd28cfa6d7c78c81a922152fe0a997892580bc2/cellphonetyping_output4.txt)
	* [input5.txt](https://gist.githubusercontent.com/kidambisrinivas/711656dde203b82f421a3ef5283de835/raw/292aa428fea5825449ddf33329a02cc11e4d8dd0/cellphonetyping_input5.txt), [output5.txt](https://gist.githubusercontent.com/kidambisrinivas/2ca2ac3ce9a58b3e28fc013d9be9d4ed/raw/2d8006d719b323898b3687a32a8a7d4447c28760/cellphonetyping_output5.txt)


## Solution

* Build a trie on 26 characters letter-set [26 lowercase alphabets] with standard insert and search functionality
* Every word in dictionary and query has to be comprised of only these characters
* Add all words to Trie dictionary
* Then for each word, perform a countKeyStrokes operation (which is similar to search op)
	* Initialize found = true [word found]
	* Initialize pCrawl to root of trie and scan forward letter by letter till we hit end of word
	* During the search, if at any point pCrawl->children[index] == NULL, then set found = false
		* After every letter of the word would count as keystroke since word not found
	* Else if letter in word found in Trie at this level, 
		* If current letter is first letter of word, we need user to type a keystroke (so count++)
		* Else If current letter has siblings or is an EndOfWord, we need user to type a keystroke (so count++)
		* Else, automcomplet would automatically prompt the only letter at this stage 

**Max word length:** L
**Number of words:** N
**Space Complexity:** O(ALPHABET_SIZE * L * N)
**Insert/Search/CountKeyStrokes Complexity:** O(L) per query

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