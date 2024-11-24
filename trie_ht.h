#ifndef HEADER_TRIE_HASHTABLE
#define HEADER_TRIE_HASHTABLE

/* Constants declarations */
#define MAX_NODE_MULTIPLIER 3

/* Data structure declarations */

struct _list {

  int startNode, targetNode;

  unsigned char letter;

  struct _list *next;
};

typedef struct _list *List;

struct _trie {
  int maxNode,  /* Max amount of trie nodes */
      nextNode; /* Index of next available node */
  List **transitions;
  char *finite; /* Finite states */
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
 * Returns 1 if True and 0 if False
 *
 **/
int isInTrie(Trie trie, unsigned char *w);

/**
 * hashes a transition and outputs a number between 0 and maxNode *
 * MAX_NODE_MULTIPLIER
 */
int hash_function(int state, unsigned char c, int maxNode);

/* End function prototypes */

#endif
