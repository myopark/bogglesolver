
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct lnode 
{
    char *word;
    struct lnode *next;
};

typedef struct 
{
    struct lnode *head;
    struct lnode *tail;
}list;

bool createLinkedList(list **ls);
bool destroyLinkedList(list **ls);

bool insertNode(list **ls, char letter);
bool removeNode(list **ls);
char *getWord(list **ls);