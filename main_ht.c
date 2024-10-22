#include "limits.h"
#include "string.h"
#include "trie_ht.h"
#include <stdio.h>
#include <stdlib.h>

/* Inserts prefixes starting with the smallest one */
void insertPrefixes(Trie trie, unsigned char *w) {
  int length = strlen((char *)w);
  unsigned char prefix[length + 1];

  for (int i = 0; i < length; i++) {
    strncpy((char *)prefix, (char *)w, i + 1);
    prefix[i + 1] = '\0';
    insertInTrie(trie, prefix);
  }
}

/* Inserts suffixes starting with the smallest one */
void insertSuffixes(Trie trie, unsigned char *w) {
  int length = strlen((char *)w);
  unsigned char suffix[length + 1];

  for (int i = length - 1, copyCount = 1; i >= 0; i--, copyCount++) {
    memcpy(suffix, &w[i], copyCount);
    suffix[copyCount] = '\0';
    insertInTrie(trie, suffix);
  }
}


/* Inserts the factors starting with the prefixes of the longest suffix until we reach the prefixes of the shortest suffixes */
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
  unsigned char *w2 = (unsigned char *)"abaa";

  printf("Adding prefixes, suffixes and factors of the word: %s\n", w1);

  insertSuffixes(trie, w1);

  int count = 0;
  for (int i = 0; i < maxNode; i++) {
    if (trie->finite[i] == 1) {
      count++;
    }
  }

  printf("isInTrie: %d\n", isInTrie(trie, w2));

  return 0;
}
