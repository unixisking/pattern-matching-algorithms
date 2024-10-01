#include <stdio.h>
// #include "trie-tm.h"
#include "trie-hashtable.h"
#include <stdlib.h>
#include "limits.h"
    // Trie trie = createTrie(10);
    // unsigned char *w = (unsigned char*) "tac";
    // unsigned char *w3 = (unsigned char*) "tob";
    
    // insertInTrie(trie, w);
    // insertInTrie(trie, w3);

    // printf("\nnextNode %d\n", trie->nextNode);


    // for(int i = 0; i < UCHAR_MAX; i++) {
    //     if(trie->transitions[i] != NULL) {
    //         printf("currentNode %d\n ", i);
    //         for(int j = 0; j < UCHAR_MAX; j++) {
    //             if(trie->transitions[i][j] != -1) {
    //                 printf("transition to node %d with char %c, ", trie->transitions[i][j], j);
    //             }

    //         }


    //         printf("\nEnd current node %d\n", i);
    //     }

    // }

    // unsigned char *check = (unsigned char*) "tob";
    // printf("is %s in trie: %d\n",check, isInTrie(trie, check));


    /* trie-hashtable.c */
int main() {


int maxNode = 13;
    Trie trie = createTrie(maxNode);

    // Insert words into the trie
    unsigned char *w1 = (unsigned char *)"tobi";
    unsigned char *w3 = (unsigned char *)"to";
    unsigned char *different = (unsigned char *)"tbo";
    // unsigned char *w2 = (unsigned char *)"tob";
    // insertInTrie(trie, w1);
    // insertInTrie(trie, w2); // Added second word insertion

    insertPrefixes(trie, w1);
    printf("\nreturn : %d\n", isInTrie(trie, different));

    printf("isIn: %d", isInTrie(trie, w3));

    return 0;
}