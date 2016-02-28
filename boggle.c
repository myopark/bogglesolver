#include <stdio.h>
#include <trie.h>

/* Unity Internship Challenge that is suppose to solve the game of Boggle and add up the score*/

struct Results{
	const char* const* Words; // pointers to unique found words
	unsigned Count; //total number of words found
	unsigned Score; //total score for all words found
	void* UserData; //ignored
};

FILE *fp;
typedef struct trie *t;
const char* b;
struct Results *r;

int main();
void LoadDictionary(const char* path);
Results FindWords(const char* board, unsigned width, unsigned height);
void FreeWords();
void FreeDictionary();

int main(){
	char *mode;
	const char word[9];
	b = {'a', 'd' , 'f',
		 'c', 't', 'o',
		 'b', 'o', 'g'};

	mode = "r";
	intialize(t);
	fp = fopen("dictionary.txt", mode );
	if (fp == NULL){
		fprintf(stderr, "Cannot open input file\n");
	}

	while(fscanf(fp, "%s", word) != EOF){
		LoadDictionary(word);
	}
	fclose(fp);

	FindWords(b, 3, 3);
	FreeWords(r);
	FreeDictionary();
	return 0;
}
// // input dictionary is a file with one word per line
void LoadDictionary(const char* path){
	int i;
	int size;
	size = sizeof(path) / sizeof(path[0]);
	for(i = 0; i < size, ++i){
		insert(t, path[i]);
	}
	return;
} // << TODO

// // this func may be called multiple times
// // board: will be exactly width * height chars, and 'q' represents the 'qu' Boggle cube
Results FindWords(const char* board, unsigned width, unsigned height){
	int i;







	return r;
} // << TODO

// // 'results' is identical to what was returned from FindWords
void FreeWords(Results results){
}// << TODO
void FreeDictionary(){
} // << TODO

 

