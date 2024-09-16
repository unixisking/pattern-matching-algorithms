#ifndef HEADER_TRIE_TM
#define HEADER_TRIE_TM

/* Data structure declarations */

struct _trie {
	int maxNode; /* maximum number of trie nodes */
	int nextNode; /* Index of next available node */
	int **transitions; /* transition matrix */
	char *finite; /* finite states  */
};

typedef struct _trie *Trie;

/* End data structure declarations */

/* Function prototypes */

/**
 *
 * Creates a trie and returns it
 * maxNode: takes max amount of nodes as input
 *
 * */
Trie createTrie(int maxNode);

/**
 *
 * Inserts a word to the trie
 * Args: takes trie and word as inputs
 *
 * */
void insertInTrie(Trie trie, unsigned char *w);

/**
 *
 * Checks whether word exist in Trie
 * Args: takes trie and word as inputs
 *
 **/
int isInTrie(Trie trie, unsigned char *w);

/* End function prototypes */

#endif
