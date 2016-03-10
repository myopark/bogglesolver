#include "boggle.h"
#include "trie.h"
#include "hashset.h"

/* Unity Internship Challenge that is suppose to solve the game of Boggle and add up the score*/
FILE *fp;
struct Results r;
trie *dict;
trie *dups;
hashset *set;

int main(int argc, char *argv[]){
    const char b[9] = {'a', 't', 'd',
                         'c', 'f', 'e',
                        'd', 'e', 'y'};

    LoadDictionary("dict.txt");
    FindWords(b, 3, 3);
    FreeDictionary();
	return 0;
}
// // input dictionary is a file with one word per line
void LoadDictionary(const char* path){

    FILE *f, *newF;
    char *line;

    f = fopen( path, "r");
    newF = fopen("dictionary.txt", "w");
    
    while ((line = getLine(f)) != NULL) {
        if (strlen(line) > 2) {
            fprintf(newF, line);
            fprintf(newF, "\n");
        }
        free(line);
    } 

    fclose(f);
    fclose(newF);

    createTrie(&dict);
    createHashSet(&set);
    createTrie(&dups);
    loadTrie(&dict, path);


} // << TODO

// // this func may be called multiple times
// // board: will be exactly width * height chars, and 'q' represents the 'qu' Boggle cube
struct Results FindWords(const char* board, unsigned width, unsigned height){
    int row, column;
    list *word;
    char** bog_board;

    bog_board = changeboard(board, bog_board, width, height);
    createLinkedList(&word);
    if(width <= 0 || height <= 0){
        printf("Illegal Board Size\n");
        exit(0);
    }

     for(row = 0; row < width ; ++row){
        for(column = 0; column < height; ++column){
            dfs(row, column, bog_board, &word, width);

         }
     }
     destroyHashSet(&set);
     deallocate(bog_board, width);
     return r;
} // << TODO

void dfs( int row, int column, char** bog_board,  list **word, int width){
    char* s;

    if( row < 0 || column < 0 || row > (width - 1) || column > (width - 1)){
        return;
    }

    if(lookUpHashVal(&set, row, column)){
        return;
    }

    insertNode(word, bog_board[row][column]);

   s = getWord(word);
   //update the struct
    if(isWord(&dict, s) && !isWord(&dups, s)){
        ++r.Count;
        ++r.Score;
        insertWord(&dups,s);
    } 
        

    if(isPrefixToWord(&dict, s)){
        insertHashVal(&set, row, column);
        //recursively go through all the directions from the point you are at
        dfs(row - 1, column, bog_board,  word, width); 
        dfs(row, column - 1, bog_board, word, width);
        dfs(row + 1, column, bog_board,  word, width); 
        dfs(row, column + 1, bog_board,  word, width);
        dfs(row - 1, column + 1, bog_board, word, width); 
        dfs(row + 1, column - 1, bog_board,  word, width); 
        dfs(row - 1, column - 1, bog_board, word, width); 
        dfs(row  + 1 , column + 1, bog_board,  word, width);
        //recursive backtracking
        removeHashVal(&set, row, column);
    }
    removeNode(word);
}
//changes the single character board into a 2d array
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

void deallocate(char** bog_board, unsigned width){
    int i;

    for(i = 0; i < width; ++i){
        free(bog_board[i]);
    }
    free(bog_board);
}

// // 'results' is identical to what was returned from FindWords
void FreeWords(struct Results results){

}
void FreeDictionary(){
    //dallocate the trie
    destroyTrie(&dict);
    destroyTrie(&dups);
} // << TODO
 
