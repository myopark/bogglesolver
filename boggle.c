#include <stdio.h>

/* Unity Internship Challenge that is suppose to solve the game of Boggle and add up the score*/

struct Results{
	const char* const* Words; // pointers to unique found words
	unsigned Count; //total number of words found
	unsigned Score; //total score for all words found
	void* UserData; //ignored
};

//TODO hash your dictionary
//Depth first search is a simple solution to this however it is going to be O(v*e)

void LoadDictionary(const char* path);
Results FindWords(const char* board, unsigned width, unsigned height);
void FreeWords();
void FreeDictionary();

// // input dictionary is a file with one word per line
void LoadDictionary(const char* path){
	return;
} // << TODO

// // this func may be called multiple times
// // board: will be exactly width * height chars, and 'q' represents the 'qu' Boggle cube
Results FindWords(const char* board, unsigned width, unsigned height){
	return;
} // << TODO

// // 'results' is identical to what was returned from FindWords
void FreeWords(Results results){
	return;
}// << TODO
void FreeDictionary(){
	return;
} // << TODO

 

