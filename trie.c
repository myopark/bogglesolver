#include "trie.h"


bool createTrie(trie **dict)
{   
    int i;
    *dict = malloc(sizeof(trie));
    if (*dict == NULL) return false;
    (*dict)->children = malloc(sizeof(struct node *) * 26);
    if ((*dict)->children == NULL)
    {
    fprintf(stderr, "malloc error\n");
    return false;
    }
    for (i = 0; i < 26; i++) 
    {
    (*dict)->children[i] = NULL;
    }
    return true;
}

bool destroyTrie(trie **dict)
{
    deleteTNode((*dict)->children);
    free(*dict);
    return true;
}

bool deleteTNode(struct tnode **letters) 
{
    int i;
    // input should never be NULL
    if (letters == NULL)
    {
    fprintf(stderr, "warning: attempting to free empty node\n");
    return false;
    }
    // depth first freeing of children
    for (i = 0; i < 26; i++)
    {
    if (letters[i] != NULL)
    {
        deleteTNode(letters[i]->children);
        free(letters[i]);
    }
    }
    free(letters);

    return true;
}

bool insertTNode(struct tnode **letters, char letter, bool isWord) 
{
    int i;
    // find index of new node and malloc space for it
    letters[letter - 97] = malloc(sizeof(struct tnode));
    if (letters[letter - 97] == NULL) 
    {
    fprintf(stderr, "malloc error\n");
    return false;   
    }

    // set data for new node 
    letters[letter - 97]->isWord = isWord;
    letters[letter - 97]->children = malloc(sizeof(struct tnode *) * 26);
    if (letters[letter - 97]->children == NULL)
    {
    fprintf(stderr, "malloc error\n");
    return false;
    }
    for (i = 0; i < 26; i++)
    {
    letters[letter - 97]->children[i] = NULL;
    }

    return true;
}

bool insertWord(trie **dict, char *word)
{
    // loop through letters until last letter in word
    // walk though dict as we loop
    int i;
    char letter;

    struct tnode **curr = (*dict)->children;
    for (i = 0; i < strlen(word) - 1; i++)
    {
    // uppercase to lowercase
    if ((letter = word[i]) < 97) 
    {
        letter += 32;
    }

    // if letter does not exist, insert into dict
    if (curr[letter - 97] == NULL)
    {
        insertTNode(curr, letter, false);
    }
    curr = curr[letter - 97]->children;
    }
    // update variables for last letter
    if ((letter = word[strlen(word) - 1]) < 97) 
    {
        letter += 32;     
    }

    // if last letter exists, update isWord
    if (curr[letter - 97] != NULL)
    {
        printf("setting laste letter to true\n");
        curr[letter - 97]->isWord = true;
    }
    // create node otherwise
    else
    {
        insertTNode(curr, letter, true);
    }

    return true;
}

bool loadTrie(trie **dict, const char *file)
{
    char *line;
    FILE *fp;

    if ((fp = fopen(file, "r")) == NULL) 
    {
        return false;
    }
    
    while ((line = getLine(fp)) != '\0')  
    {
        insertWord(dict, line); // one word per line
        free(line);
    }

    fclose(fp);
    return true;
}

// code from Stan Eisenstat's CS323
char *getLine(FILE *fp) 
{
    char *line;
    int size;
    int c, i;

    size = sizeof(double);
    line = malloc(size);
    for (i = 0; (c = getc(fp)) != EOF ; ) 
    {
    if (i == size - 1) 
    {
            size *= 2;                  // Double allocation
        line = realloc(line, size);
    }
    line[i++] = c;
    if (c == '\n')              // Break on newline
    {   
            i = i - 1;
        break;
    }
    }

    if ((c == EOF || c == '\n') && i == 0)  // Check immediate EOF
    {   
    free(line);
    return NULL;
    }
         
    line[i++] = '\0';               // Terminate line
    line = realloc(line, i);            // Trim excess storage

    return (line);
}

bool isPrefixToWord(trie **dict, char *str)
{
    char letter;
    int i;
    struct tnode **curr = (*dict)->children;
    for (i = 0; i < strlen(str); i++)
    {
    // uppercase to lowercase
        if ((letter = str[i]) < 97){
            letter += 32;
        }       
    // if letter does not exist, not a prefix. 
        if (curr[letter - 97] == NULL){
            return false; 
            letter += 32;
        }       
    // if letter does not exist, not a prefix. 
        if (curr[letter - 97] == NULL){
            return false; 
        }
         curr = curr[letter - 97]->children;
    }
    return true;
}

bool isWord(trie **dict, char *str)
{
    char letter;
    int i;
    struct tnode **curr = (*dict)->children;
    for (i = 0; i < strlen(str); i++)
    {
    // uppercase to lowercase
        if ((letter = str[i]) < 97)
        {
            letter += 32;
        }
      

    // if letter does not exist, not a word. 
        if (curr[letter - 97] == NULL)
        {
            // printf("letter does not exist\n");
            return false; 
        }
    // if last character and isWord, return true
        else if (curr[letter - 97]->isWord && (i == strlen(str) - 1))
        {
            return true;
        }
        curr = curr[letter - 97]->children;
    }
    // printf("blehb\n");
    return false;
}


































// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "trie.h"


// trie_node_t *getNode(void)
// {
//     trie_node_t *pNode = NULL;
 
//     pNode = (trie_node_t *)malloc(sizeof(trie_node_t));
 
//     if( pNode )
//     {
//         int i;
 
//         pNode->value   = 0;
 
//         for(i = 0; i < ALPHABET_SIZE; i++)
//         {
//             pNode->children[i] = NULL;
//         }
//     }
 
//     return pNode;
// }
 
// void initialize(trie_t *pTrie)
// {
//     pTrie->root = getNode();
//     pTrie->count = 0;
// }
 
// void insert(trie_t *pTrie, char key[])
// {  
//     int level;
//     int length = strlen(key);
//     int index;
//     trie_node_t *pCrawl;
 
//     pTrie->count++;
//     pCrawl = pTrie->root;
 
//     for( level = 0; level < length; level++ )
//     {
//         index = CHAR_TO_INDEX(key[level]);
//         if( !pCrawl->children[index] )
//         {
//             pCrawl->children[index] = getNode();
//         }
 
//         pCrawl = pCrawl->children[index];
//     }
 
//     // mark last node as leaf
//     pCrawl->value = pTrie->count;
// }

// int search(trie_t *pTrie, char key[])
// {
//     int level;
//     int length = strlen(key);
//     int index;
//     trie_node_t *pCrawl;
 
//     pCrawl = pTrie->root;
 
//     for( level = 0; level < length; level++ )
//     {
//         index = CHAR_TO_INDEX(key[level]);
//         if(!pCrawl->children[index] )
//         {
//             return 0;
//         }
 
//         pCrawl = pCrawl->children[index];
//     }
//     return (!pCrawl->value);
// }










