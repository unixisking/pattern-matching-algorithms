#include <stdio.h>
#include <stdlib.h>
#include "limits.h"
#include "trie_tm.h"

Trie createTrie(int maxNode) {
    Trie trie = malloc(sizeof(struct _trie));
    if(trie == NULL) { return NULL; }

    trie->maxNode = maxNode;
    trie->nextNode = 0;
    trie->transitions = malloc(sizeof(int*) * maxNode);

    if(trie->transitions == NULL) {
        free(trie);
        return NULL;
    }

    for(int i = 0; i < maxNode; i++) {
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

    for(unsigned char *currentChar = w; *currentChar != '\0'; currentChar++) {
        if(trie->nextNode == trie->maxNode) {
            return;
        }

        if(trie->transitions[currentNode] == NULL) {
            trie->transitions[currentNode] = malloc(sizeof(int) * UCHAR_MAX);
            for(int i = 0; i < UCHAR_MAX; i++) {
                trie->transitions[currentNode][i] = -1;
            }
        }

        if(trie->transitions[currentNode][*currentChar] == -1) {
            trie->transitions[currentNode][*currentChar] = ++trie->nextNode;
        }

        currentNode = trie->transitions[currentNode][*currentChar];
    }

    trie->finite[currentNode] = 1;


}

int isInTrie(Trie trie, unsigned char *w) {
    if (trie == NULL) {
        return 1;
    }

    int currentNode = 0;
    for(unsigned char *currentChar = w; *currentChar != '\0'; currentChar++) {
        if(trie->transitions[currentNode] == NULL || trie->transitions[currentNode][*currentChar] == -1) {
            return 1;
        }
        currentNode = trie->transitions[currentNode][*currentChar];
    }

    
    return trie->finite[currentNode] == 1 ? 0 : 1;
}
