#include <stdio.h>
#include <stdlib.h>
#include "limits.h"
#include "string.h"
#include "trie_ht.h"

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

int main() {
    int maxNode = 8;
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
    printf("finite states = %d", count);
    printf("\n");
    printf("nextode= %d", trie->nextNode);
   
    return 0;
}
