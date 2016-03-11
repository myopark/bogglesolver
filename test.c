#include "boggle.h"


struct Results r;

int main(int argc, char *argv[]){
    const char b[9] = {'a', 't', 'd',
                         'c', 'f', 'e',
                        'd', 'e', 'y'};

    LoadDictionary("dict.txt");
    FindWords(b, 3, 3);
    if(r.Count == 4){
    	printf("yo");
    }
    FreeDictionary();
    FreeWords();
	return 0;
}