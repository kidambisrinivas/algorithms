#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std; 
  
const int ALPHABET_SIZE = 36; 
  
// trie node 
struct TrieNode 
{ 
    TrieNode *children[ALPHABET_SIZE];
    int nextNum;
  
    // isEndOfWord is true if the node represents 
    // end of a word 
    bool isEndOfWord; 
}; 
  
// Returns new trie node (initialized to NULLs) 
TrieNode* getNode() 
{ 
    TrieNode *pNode =  new TrieNode; 
    pNode->isEndOfWord = false; 
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        pNode->children[i] = NULL;
    pNode->nextNum = 0;   
    return pNode; 
} 
  
// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(TrieNode *root, string key) 
{ 
    TrieNode *pCrawl = root; 
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - 'a';
        if(index < 0)
            index = key[i] - '0' + 26;
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
} 
  
// Returns true if key presents in trie, else 
// false 
bool search(TrieNode *root, string key) 
{ 
    TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - 'a';
        if(index < 0)
            index = key[i] - '0' + 26;
        if (pCrawl->children[index] == NULL)
            return false;  
        pCrawl = pCrawl->children[index]; 
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
}

string getStr(int num) {
    ostringstream str1; 
    str1 << num;
    return str1.str();
    //char snum[6];
    //itoa(num, snum, 10);
    //string str1(snum);
    //cout << str1;
    //return str1;
}

const char digit_pairs[201] = {
  "00010203040506070809"
  "10111213141516171819"
  "20212223242526272829"
  "30313233343536373839"
  "40414243444546474849"
  "50515253545556575859"
  "60616263646566676869"
  "70717273747576777879"
  "80818283848586878889"
  "90919293949596979899"
};

std::string itostr(unsigned val)
{
    string s;
    if(val==0)
    {
        s="0";
        return s;
    }

    int size;
    if(val>=10000)
    {
        if(val>=10000000)
        {
            if(val>=1000000000)
                size=10;
            else if(val>=100000000)
                size=9;
            else 
                size=8;
        }
        else
        {
            if(val>=1000000)
                size=7;
            else if(val>=100000)
                size=6;
            else
                size=5;
        }
    }
    else 
    {
        if(val>=100)
        {
            if(val>=1000)
                size=4;
            else
                size=3;
        }
        else
        {
            if(val>=10)
                size=2;
            else
                size=1;
        }
    }

    s.resize(size);
    char* c = &s[size-1];
    while(val>=100)
    {
       int pos = val % 100;
       val /= 100;
       *(short*)(c-1)=*(short*)(digit_pairs+2*pos); 
       c-=2;
    }
    while(val>0)
    {
        *c--='0' + (val % 10);
        val /= 10;
    }
    return s;
}

// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
string searchAndInsert(TrieNode *root, string key) 
{ 
    TrieNode *pCrawl = root;
    bool found = true;
    string suffix = "";
    for (int i = 0; i < key.length(); i++) 
    {
        int index = key[i] - 'a';
        if(index < 0)
            index = key[i] - '0' + 26;
        if (pCrawl->children[index] == NULL) { 
            pCrawl->children[index] = getNode(); 
            found = false;
        }
  
        pCrawl = pCrawl->children[index];
        if(i == key.length()-1 && !pCrawl->isEndOfWord)
            found = false;
    }
    if(found) {
        TrieNode* leaf = pCrawl;
        for(int num=0; ; num++) {
            pCrawl = leaf;
            found = true;
            // string addKey = getStr(num);
            string addKey = itostr(num);
            // cout << "check: " << addKey << endl;
            for(int i=0; i<addKey.length(); i++) {
                int index = addKey[i] - 'a';
                if(index < 0)
                    index = addKey[i] - '0' + 26;

                // cout << "key: " << addKey[i] << ", index: " << index << endl;
                if (pCrawl->children[index] == NULL) { 
                    pCrawl->children[index] = getNode(); 
                    found = false;
                }
                pCrawl = pCrawl->children[index];
                if(i == addKey.length()-1 && !pCrawl->isEndOfWord)
                    found = false;
            }
            if(found == false) {
                suffix = addKey;
                // cout << "success: " << num << ", suffix: " << suffix << endl;
                break;
            }
        }
    }
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
    return suffix;
} 

double round(double var) 
{ 
    // 37.66666 * 100 =3766.66 
    // 3766.66 + .5 = 3767.16    for rounding off value 
    // then type cast to int so value is 3766 
    // then divided by 100 so the value converted into 37.66 
    double value = (int)(var * 100 + .5); 
    return (double)value / 100; 
}

int main() {
    int N;
    while(cin >> N) {
        string word;
        TrieNode *root = getNode();
        for(int i=0; i<N; i++) {
            cin >> word;
            string suffix = searchAndInsert(root, word);
            cout << word;
            if(suffix != "")
                cout << suffix;
            cout << endl;
        }
    }
    return 0;
}