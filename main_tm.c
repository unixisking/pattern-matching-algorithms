#include "limits.h"
#include "string.h"
#include "trie_tm.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void insertPrefixes(Trie trie, unsigned char *w) {
  int length = strlen((char *)w);
  unsigned char prefix[length + 1];

  for (int i = 0; i < length; i++) {
    strncpy((char *)prefix, (char *)w, i + 1);
    prefix[i + 1] = '\0';
    insertInTrie(trie, prefix);
  }
}

void insertSuffixes(Trie trie, unsigned char *w) {
  int length = strlen((char *)w);
  unsigned char suffix[length + 1];

  for (int i = length - 1, copyCount = 1; i >= 0; i--, copyCount++) {
    memcpy(suffix, &w[i], copyCount);
    suffix[copyCount] = '\0';
    insertInTrie(trie, suffix);
  }
}

void insertFactors(Trie trie, unsigned char *w) {
  int length = strlen((char *)w);
  unsigned char suffix[length + 1];

  for (int i = 0, copyCount = length; i < length; i++, copyCount--) {
    memcpy(suffix, &w[i], copyCount);
    suffix[copyCount] = '\0';
    insertInTrie(trie, suffix);
    insertPrefixes(trie, suffix);
  }
}

int main() {
  int maxNode = 100;
  Trie trie = createTrie(maxNode);
  unsigned char *w1 = (unsigned char *)"abaababa";

  // insertInTrie(trie, w1);

  insertFactors(trie, w1);

  int count = 0;
  for (int i = 0; i < maxNode; i++) {
    if (trie->finite[i] == 1) {
      count++;
    }
  }
  printf("\n");
  printf("finite states = %d", count);
  printf("\n");
  printf("nextode= %d", trie->nextNode);
  /*
  int count = 0;
  for(int i = 0; i < maxNode; i++) {
      if(trie->finite[i] == 1) {
          count++;
      }

  }
  */
  // printf("m = %d", count);
  /*tmri   r
  for(int i = 0; i < UCHAR_MAX; i++) {
      if(trie->transitions[i] != NULL) {
          printf("currentNode %d\n ", i);
          for(int j = 0; j < UCHAR_MAX; j++) {
              if(trie->transitions[i][j] != -1) {
                  printf("transition to node %d with char %c, ",
  trie->transitions[i][j], j);
              }

          }


          printf("\nEnd current node %d\n", i);
      }

  }
  */
}
