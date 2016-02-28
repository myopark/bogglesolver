#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <trie.c>
 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
 
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

trie_node_t *getNode(void);
void initialize(trie_t *pTrie);
void insert(trie_t *pTrie, char key[]);
int search(trie_t *pTrie, char key[]);
int main();