#include "trie-tm.h"
#include <stdio.h>
#include <stdlib.h>
#include "limits.h"

Trie createTrie(int maxNode) {
    Trie trie = malloc(sizeof(struct _trie));
    if(trie == NULL) {
        return NULL;
    }

    trie->maxNode = maxNode;
    trie->nextNode = 0;
    trie->transitions = malloc(sizeof(int*) * 10);

    if(trie->transitions == NULL) {
        free(trie);
        return NULL;
    }

    for(int i = 0; i < UCHAR_MAX; i++) {
        trie->transitions[i] = NULL;
    }

    trie->finite = malloc(sizeof(char) * maxNode);

    if(trie->finite == NULL) {
        free(trie->transitions);
        free(trie);
        return NULL;
    }
    
    for(int i = 0; i < maxNode; i++) {
        trie->finite[i] = 0;
    }

    return trie;
}

void insertInTrie(Trie trie, unsigned char *w) {

    if(trie == NULL) {
        return;
    }

    int currentNode = 0;

    printf("current word %s\n", w);
    for(unsigned char *currentChar = w; *currentChar != '\0'; currentChar++) {
        printf("\n");
        printf("current character %c\n", *currentChar);
        if(trie->nextNode == trie->maxNode) {
            return;
        }

        // Add char when transitions table for a specific node is not allocated
        if(!trie->transitions[currentNode]) {
            printf("first if");
            trie->transitions[currentNode] = malloc(sizeof(int) * UCHAR_MAX);
            trie->transitions[currentNode][*currentChar] = ++trie->nextNode;
            currentNode++;
        }

        // Add char when we can not find a transition
        else if(!trie->transitions[currentNode][*currentChar]) {
            printf("second condition");
            trie->transitions[currentNode][*currentChar] = ++trie->nextNode;
            currentNode++;
        }

        // When we can find a transition with the current character
        else {
            printf("else");
            currentNode = trie->transitions[currentNode][*currentChar];
        }


        /*if(trie->transitions[currentNode] != NULL && trie->transitions[currentNode][*currentChar] != -1) {*/
        /*    currentNode = trie->transitions[currentNode][*currentChar];*/
        /*}*/
        /*printf("currentNode %d\n", currentNode);*/
    }


}

int isInTrie(Trie trie, unsigned char *w) {
    return 1;
}
