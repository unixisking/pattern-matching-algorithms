#include "trie-hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    /* If trie is null then bail */
    if(trie == NULL) { return; }

    int currentState = 0;
    for(unsigned char *currentChar = w; *currentChar != '\0'; currentChar++) {
        int hash = hash_function(currentState, *currentChar, trie->maxNode);

        /* No hash collision: allocate List for transition */
        if(trie->transitions[hash] == NULL) {
            trie->transitions[hash] = malloc(sizeof(List));
            *trie->transitions[hash] = NULL;
        }

        List currentNode = *trie->transitions[hash];
        List prevNode = NULL;
        int transitionFound = 0;

        while(currentNode != NULL) {
            /*
             * When encountering a char that was already added 
             * with the same state then skip creation of newNode 
             * */

            if(currentNode->letter == *currentChar && currentState == currentNode->startNode) {
                transitionFound = 1;
                currentState = currentNode->targetNode;
                break;
            }
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        if(transitionFound == 0) {
            List newNode = malloc(sizeof(struct _list));

            newNode->startNode = currentState;
            newNode->letter = *currentChar;
            newNode->targetNode = ++trie->nextNode;
            newNode->next = NULL;

            if(prevNode == NULL) {
                *trie->transitions[hash] = newNode;
            }
            else {
                prevNode->next = newNode;
            }
            currentState = newNode->targetNode;
        }
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

void insertPrefixes(Trie trie, unsigned char *w) {
    int length = strlen((char *) w);
    unsigned char prefix[length + 1];

    for(int i = 0; i < length; i++) {
        strncpy((char*) prefix, (char *) w, i+1);
        prefix[i+1]='\0';
        insertInTrie(trie, prefix);
    }

}

void insertSuffixes(Trie trie, unsigned char *w) {
    int length = strlen((char *) w);
    unsigned char suffix[length + 1];

    for(int i = length - 1, copyCount = 1; i >= 0; i--, copyCount++) {
        memcpy(suffix, &w[i], copyCount);
        suffix[copyCount] = '\0';
        insertInTrie(trie, suffix);
    }
}

/* Add all prefixes of all suffixes starting with the biggest suffix */
void insertFactors(Trie trie, unsigned char *w) {
    int length = strlen((char *) w);
    unsigned char suffix[length + 1];

    for(int i = 0, copyCount = length; i < length; i++, copyCount--) {
        memcpy(suffix, &w[i], copyCount);
        suffix[copyCount] = '\0';
        insertInTrie(trie, suffix);
        insertPrefixes(trie, suffix);
    }
}
