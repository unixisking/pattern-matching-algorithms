#include <stdio.h>
#include "trie-tm.h"
#include "limits.h"

int main() {
    Trie trie = createTrie(10);
    unsigned char *w = (unsigned char*) "tac";
    unsigned char *w3 = (unsigned char*) "tob";
    
    insertInTrie(trie, w);
    insertInTrie(trie, w3);

    printf("\nnextNode %d\n", trie->nextNode);


    for(int i = 0; i < UCHAR_MAX; i++) {
        if(trie->transitions[i] != NULL) {
            printf("currentNode %d\n ", i);
            for(int j = 0; j < UCHAR_MAX; j++) {
                if(trie->transitions[i][j]) {
                    printf("transition to node %d with char %c, ", trie->transitions[i][j], j);
                }

            }


            printf("\nEnd current node %d\n", i);
        }

    }
    return 0;
}
