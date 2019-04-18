#include <iostream>
#include <string>
#include <vector>
using namespace std; 
  
const int ALPHABET_SIZE = 26; 
  
// trie node 
struct TrieNode 
{ 
    TrieNode *children[ALPHABET_SIZE]; 
  
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
        if (pCrawl->children[index] == NULL)
            return false;  
        pCrawl = pCrawl->children[index]; 
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
}

// Counts number of keystrokes for system
int countKeyStrokes(TrieNode *root, string key) 
{ 
    int keystrokes = 0;
    bool found = true;
    TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++) 
    {
        if(!found) {
            keystrokes++;
            continue;
        }
        int index = key[i] - 'a'; 
        // If key not found in dictionary, return -1 as number of keystrokes
        if (pCrawl->children[index] == NULL) {
            keystrokes++;
            found = false;
            continue;
        }
        // Check if there's only 1 child
        int nonNullChildren = 0;
        for(int i=0; i<ALPHABET_SIZE; i++)
            if(pCrawl->children[i] != NULL)
                nonNullChildren++;
        if(i == 0 || (nonNullChildren != 1 || pCrawl->isEndOfWord))
            keystrokes++;
        // cout << "children: " << nonNullChildren << endl;
        pCrawl = pCrawl->children[index];
    }
    // cout << "key: " << key << ", count: " << keystrokes << endl;
    return keystrokes; 
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
        vector<string> words;
        TrieNode *root = getNode();
        for(int i=0; i<N; i++) {
            cin >> word;
            insert(root, word);
            words.push_back(word);
        }
        int totalKeystrokes = 0;
        for(int i=0; i<(int)words.size(); i++) {
            totalKeystrokes = totalKeystrokes + countKeyStrokes(root, words[i]);
        }
        double avgKeystrokes = (double)totalKeystrokes / (double)words.size();
        printf("%.2f\n", avgKeystrokes);
        delete root;
    }
    return 0;
}