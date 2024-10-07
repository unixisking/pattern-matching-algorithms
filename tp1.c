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


int maxNode = 100;
    Trie trie = createTrie(maxNode);

    unsigned char *w1 = (unsigned char *)"abaababa";

    insertFactors(trie, w1);

    int count = 0;
    for(int i = 0; i < maxNode; i++) {
        if(trie->finite[i] == 1) {
            count++;
        }
    }
    printf("\n");
    printf("m = %d", count);

    return 0;
}
