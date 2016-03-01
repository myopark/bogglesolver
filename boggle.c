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
const char* const* list;


int main(int argc, char *argv[]);
void LoadDictionary(const char* path);
struct Results FindWords(const char* board, unsigned width, unsigned height);
void dfs(int row, int column, char** bog_board,  char* s, int** visited, int width);
char** changeboard(const char* board, char** bog_board, unsigned width, unsigned height);
int** intializeV(int** visited, unsigned width, unsigned height);
void deallocate(char** bog_board, unsigned width);
void deallocateV(int** visited, unsigned width);
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
    int** visited;
    char s[10];
    char** bog_board;

    bog_board = changeboard(board, bog_board, width, height);
    visited = intializeV(visited, width, height);

    if(width == 0 || height == 0){
        printf("Illegal Board Size\n");
        return;
    }

     for(row = 0; row < width ; ++row){
        for(column = 0; column < height; ++column){
            dfs(row, column, bog_board, s, visited, width);
         }
     }
     //need to add a list to R-> words
     //need to update score
     //need to updat count, which should be the size of that list that you put words in
     deallocate(bog_board, width);
     deallocateV(visited,width);
return;
} // << TODO

void dfs( int row, int column, char** bog_board,  char* s, int** visited, int width){
    int i; 

    if( row < 0 || column < 0 || row > (width - 1) 
        || column > (width - 1)){
        return;
    }
    if(visited[row][column]){
        return;
    }
    //TODO make a list of words found
    int results, score;
    size_t len, sLength;

    sLength = strlen(s);
    s[sLength++] = bog_board[row][column];
    s[sLength] = '\0';

    visited[row][column] = 1;
    results = search(&trie, s);
    if(!results){
        visited[row][column] = 1;
        return;
    }
    //TODO make a isword function or some form of indicator that it is a word
    else if(results && isWord()){
    }
    //TODO: Fix this so it will match the 1d array, not a 2d array
    dfs(row - 1, column, bog_board, s, visited, width); 
    dfs(row, column - 1, bog_board, s, visited, width);
    dfs(row + 1, column, bog_board, s, visited, width); 
    dfs(row, column + 1, bog_board, s, visited, width); 

    printf("%s\n", s);
    visited[row][column] = 0;
}

char** changeboard(const char* board, char** bog_board, unsigned width, unsigned height){
    int i, j, index;
    bog_board = malloc(width * sizeof *bog_board);
    for( i = 0; i < width; ++i){
        bog_board[i] = malloc(height * sizeof *bog_board[i]);
    }
    index = 0;
    for(i = 0; i < width; ++i){
        for( j = 0; j < height; ++j){
            bog_board[i][j] = board[index];
            ++index;
        }
    }
    return bog_board;
}

int** intializeV(int** visited, unsigned width, unsigned height){
    int i, j;
    visited = malloc(width * sizeof *visited);
    for( i = 0; i < width; ++i){
        visited[i] = malloc(height * sizeof *visited[i]);
    }
    for(i = 0; i < width; ++i){
        for (j = 0; j < height; ++j){
            visited[i][j] = 0;
        }
    }
    return visited;
}

void deallocate(char** bog_board, unsigned width){
    int i;

    for(i = 0; i < width; ++i){
        free(bog_board[i]);
    }
    free(bog_board);
}

void deallocateV(int** visited, unsigned width){
      int i;

    for(i = 0; i < width; ++i){
        free(visited[i]);
    }
    free(visited);
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
