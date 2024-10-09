# Trie Data Structure

This repository contains an implementation of a **Trie** (prefix tree) in C, a data structure used to store and search strings efficiently, especially useful in applications like autocomplete and spell-check.

## Features

- **Insert words** into the Trie.
- **Search words** to check their existence in the Trie.
- **Add Prefixes** of a word
- **Add Suffixes** of a word
- **Add Factors** of a word


```c
Trie createTrie(int maxNode);
void insertInTrie(Trie trie, unsigned char *w);
int isInTrie(Trie trie, unsigned char *w);
```

## Project Structure

### Transition table implementation

- `trie-tm.h`: Header file containing Trie structure definitions and function prototypes.
- `trie-tm.c`: Source file with function implementations for the Trie operations.
- `main_tm.c`: Example usage by adding the word the prefixes, suffixes, and the factors of "abaababa"


```c
struct _trie {
	int maxNode; /* maximum number of trie nodes */
	int nextNode; /* Index of next available node */
	int **transitions; /* transition matrix */
	char *finite; /* finite states  */
};

typedef struct _trie *Trie;

```

#### Usage

And to run the transition table implementation :

```c

make trie_tm && ./trie_tm

```

### Hashtable based implementation

- `trie-ht.h`: Header file containing Trie structure definitions and function prototypes.
- `trie-ht.c`: Source file with function implementations for the Trie operations.
- `main_ht.c`: Example usage by adding the word the prefixes, suffixes, and the factors of "abaababa"

```c

struct _list {
    int startNode,
        targetNode;
    unsigned char letter;
    struct _list *next;
};

typedef struct _list *List;

struct _trie {
    int maxNode, /* Max amount of trie nodes */
        nextNode; /* Index of next available node */
    List **transitions; /* Adjacency list */
    char *finite; /* Finite states */
};

typedef struct _trie *Trie;

```


#### Usage

To run the hash table implementation :


```c

make trie_ht && ./trie_ht

```



