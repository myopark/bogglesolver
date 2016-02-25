#include <stdio.h>

/* Unity Internship Challenge that is suppose to solve the game of Boggle and add up the score*/

struct Results{
	const char* const* Words;
	unsigned Count;
	unsigned Score;
	void* UserData;
};

void LoadDictionary(const char* path);
Results FindWords(const char* board, unsigned width, unsigned height);
void FreeWords();
void FreeDictionary();

// // input dictionary is a file with one word per line

void LoadDictionary(const char* path); // << TODO

// // this func may be called multiple times

// // board: will be exactly width * height chars, and 'q' represents the 'qu' Boggle cube

 Results FindWords(const char* board, unsigned width, unsigned height); // << TODO

// // 'results' is identical to what was returned from FindWords

 void FreeWords(Results results); // << TODO

 void FreeDictionary(); // << TODO

 

