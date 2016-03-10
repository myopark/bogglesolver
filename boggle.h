#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
struct Results{
	const char* const* Words; // pointers to unique found words
	unsigned Count; //total number of words found
	unsigned Score; //total score for all words found
	void* UserData; //ignored
};


int main(int argc, char *argv[]);
void LoadDictionary(const char* path);
struct Results FindWords(const char* board, unsigned width, unsigned height);
void dfs( int row, int column, char** bog_board,  list **word, int width);
char** changeboard(const char* board, char** bog_board, unsigned width, unsigned height);
int** intializeV(int** visited, unsigned width, unsigned height);
void deallocate(char** bog_board, unsigned width);

void FreeWords();
void FreeDictionary();