#include "trie-hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include "limits.h"

int hash_function(int state, unsigned char c, int maxNode) {
    int m = maxNode * MAX_NODE_MULTIPLIER;
    int prime = 31;
    return (state * prime + c) % m;
}

Trie createTrie(int maxNode) {
    int maxTransitions = maxNode * MAX_NODE_MULTIPLIER;
    Trie trie = malloc(sizeof(struct _trie));
    if(trie == NULL) { return NULL; }

    trie->maxNode = maxNode;
    trie->nextNode = 0;
    trie->transitions = malloc(sizeof(List) * maxTransitions);

    if(trie->transitions == NULL) {
        free(trie);
        return NULL;
    }

    for(int i = 0; i < maxTransitions;  i++) {
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

    int currentState = 0;
    for(unsigned char *currentChar = w; *currentChar != '\0'; currentChar++) {
        int hash = hash_function(currentState, *currentChar, trie->maxNode);
        printf("hash for character %c is %d\n", *currentChar, hash);

        if(trie->transitions[hash] == NULL) {
            trie->transitions[hash] = malloc(sizeof(List));
            *trie->transitions[hash] = NULL;
        }

        List currentNode = *trie->transitions[hash];
        List prevNode = NULL;

        while(currentNode != NULL) {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }

        List newNode = malloc(sizeof(struct _list));

        newNode->startNode = currentState;
        newNode->letter = *currentChar;
        newNode->targetNode = ++trie->nextNode;
        printf("target for letter %c is %d and startNode is %d and hhash is %d\n", newNode->letter, newNode->targetNode, newNode->startNode, hash);
        newNode->next = NULL;

        if(prevNode == NULL) {
            *trie->transitions[hash] = newNode;
        }
        else {
            prevNode->next = newNode;
        }
        currentState = newNode->targetNode;
    }

    trie->finite[currentState] = 1;
}

int isInTrie(Trie trie, unsigned char *w) {

    if(*w == '\0') { return 1; }

    int state = 0;
    for(unsigned char *c = w; *c != '\0'; c++) {

        int hash = hash_function(state, *c, trie->maxNode);

        if(trie->transitions[hash] != NULL) {
            List currentNode = *trie->transitions[hash];

            while(currentNode != NULL) {
                if(currentNode->letter == *c) {
                    state = currentNode->targetNode;
                    break;
                } 
                else {
                    currentNode = currentNode->next;
                }
            }
            if(currentNode == NULL) {
                return 1;
            }
        }
        else {
            return 1;
        }
    }
    return 0;
}