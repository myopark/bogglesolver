#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Unity Internship Challenge that is suppose to solve the game of Boggle and add up the score*/

//TODO: comments
//TODO: testFiles
//TODO: finish code

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
 
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
 
// trie node
typedef struct trie_node trie_node_t;
struct trie_node
{
    int value;
    trie_node_t *children[ALPHABET_SIZE];
};
 
// trie ADT
typedef struct trie trie_t;
struct trie
{
    trie_node_t *root;
    int count;
};


struct Results{
	const char* const* Words; // pointers to unique found words
	unsigned Count; //total number of words found
	unsigned Score; //total score for all words found
	void* UserData; //ignored
};

FILE *fp;
typedef struct Results *r;
trie_t trie;


int main(int argc, char *argv[]);
void LoadDictionary(const char* path);
struct Results FindWords(const char* board, unsigned width, unsigned height);
void dfs(trie_t *pTrie, int row, int column, const char* board,  char* s, int* visited, int width);
void FreeWords();
void FreeDictionary();
trie_node_t *getNode(void);
void initialize(trie_t *pTrie);
void insert(trie_t *pTrie, char key[]);
int search(trie_t *pTrie, char key[]);

int main(int argc, char *argv[]){
    const char b[9] = {'a', 't', 'd',
                         'c', 'f', 'e',
                        'd', 'e', 'y'};

    LoadDictionary("dictionary.txt");
    FindWords(b, 3, 3);
	return 0;
}
// // input dictionary is a file with one word per line
void LoadDictionary(const char* path){
    char ch;
    char word[1000];
    int i;
    char output[][32] = {"Not present in trie", "Present in trie"};

    fp = fopen(path, "r");
    initialize(&trie);

    if (fp == NULL){
        fprintf(stderr, "Cannot open input file\n");
    }

    while(fgets(word, 1000, fp) != NULL){
        //printf("%s", word);
        insert(&trie, word);
    }
    fclose(fp);
    ///need to free malloc

} // << TODO

// // this func may be called multiple times
// // board: will be exactly width * height chars, and 'q' represents the 'qu' Boggle cube
struct Results FindWords(const char* board, unsigned width, unsigned height){
    int row, column;
    int i, j;
    int visited[width*height];
    char s[10];

    //mark all of the board as visited
    for(j = 0; j < width*height; ++j){
        visited[j] = 0; 
    }

    if(width == 0 || height == 0){
        printf("Illegal Board Size\n");
        return;
    }

     for(row = 0; row < width ; ++row){
        for(column = 0; column < height; ++column){
            dfs(&trie, row, column, board, s, visited, width);
         }
     }
     //need to add a list to R-> words
     //need to update score
     //need to updat count, which should be the size of that list that you put words in

return;
} // << TODO

void dfs(trie_t *pTrie, int row, int column, const char* board,  char* s, int* visited, int width){
    if( row < 0 || column < 0 || row > (ARRAY_SIZE(board) - 1) 
        || column > (ARRAY_SIZE(board) - 1)){
        return;
    }
    if(visited[width * row + column]){
        return;
    }
    //TODO make a list of words found
    int results, score;
    size_t len, sLength;

    sLength = strlen(s);
    s[sLength++] = board[width * row + column];
    s[sLength] = '\0';

    printf("%s\n", s);

    visited[width * row + column] = 1;
    results = search(pTrie, s);
    if(!results){
        visited[width * row + column] = 1 ;
        printf("not present in trie\n");
        return;
    }
    //TODO make a isword function or some form of indicator that it is a word
    else if(results){
        //TDODO need to check if word
       printf("it is present in trie\n");
    }
    //TODO: Fix this so it will match the 1d array, not a 2d array
    // dfs(&trie, row - 1, column, board, s, visited, width); 
    // dfs(&trie, row, column - 1, board, s, visited, width);
    // dfs(&trie, row + 1, column, board, s, visited, width); 
    // dfs(&trie, row, column + 1, board, s, visited, width); 

    //turn visited to false
    //reset string??
    //backtracking spot?
    // s = "";
    visited[width * row + column] = 0;
}


// // 'results' is identical to what was returned from FindWords
void FreeWords(struct Results results){
}// << TODO
void FreeDictionary(){
} // << TODO
 

 //trie implementation
// Returns new trie node (initialized to NULLs)
trie_node_t *getNode(void)
{
    trie_node_t *pNode = NULL;
 
    pNode = (trie_node_t *)malloc(sizeof(trie_node_t));
 
    if( pNode )
    {
        int i;
 
        pNode->value = 0;
 
        for(i = 0; i < ALPHABET_SIZE; i++)
        {
            pNode->children[i] = NULL;
        }
    }
 
    return pNode;
}
 
// Initializes trie (root is dummy node)
void initialize(trie_t *pTrie)
{
    pTrie->root = getNode();
    pTrie->count = 0;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(trie_t *pTrie, char key[])
{
    int level;
    int length = strlen(key);
    int index;
    trie_node_t *pCrawl;
 
    pTrie->count++;
    pCrawl = pTrie->root;
 
    for( level = 0; level < length; level++ )
    {
        index = CHAR_TO_INDEX(key[level]);
        if( !pCrawl->children[index] )
        {
            pCrawl->children[index] = getNode();
        }
 
        pCrawl = pCrawl->children[index];
    }
 
    // mark last node as leaf
    pCrawl->value = pTrie->count;
}
 
// Returns non zero, if key presents in trie
int search(trie_t *pTrie, char key[])
{
    int level;
    int length = strlen(key);
    int index;
    trie_node_t *pCrawl;
 
    pCrawl = pTrie->root;
 
    for( level = 0; level < length; level++ )
    {
        index = CHAR_TO_INDEX(key[level]);
        if(!pCrawl->children[index] )
        {
            return 0;
        }
 
        pCrawl = pCrawl->children[index];
    }
    return (!pCrawl->value);
}