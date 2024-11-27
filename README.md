# Table of Contents

1. [Overview](#overview)
2. [Features](#features)
   - [Trie Operations](#trie-operations)
3. [Project Structure](#project-structure)
   - [Transition Table Implementation](#transition-table-implementation)
   - [Hashtable-Based Implementation](#hashtable-based-implementation)
4. [String Matching Algorithms](#string-matching-algorithms)
5. [Usage](#usage)
   - [Running Transition Table Implementation](#running-transition-table-implementation)
   - [Running Hashtable Implementation](#running-hashtable-implementation)
   - [Cleaning Executables](#cleaning-executables)

# Trie Data Structure

This repository contains an implementation of a **Trie** (prefix tree) in C, a data structure used to store and search strings efficiently, especially useful in applications like autocomplete and spell-check. Additionally, the repository includes implementations of various pattern matching algorithms.

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
void insertPrefixes(Trie trie, unsigned char *w);
void insertSuffixes(Trie trie, unsigned char *w);
void insertFactors(Trie trie, unsigned char *w);
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

## String Matching Algorithms

The repository includes implementations of several string matching algorithms:

- **Brute Force Algorithms**: Simple and direct methods to find matches in a string.
- **Morris-Pratt (MP)**: Efficient searching algorithm using a prefix function.
- **Knuth-Morris-Pratt (KMP)**: Extension of MP that optimizes prefix matching.
- **Boyer-Moore**: A highly efficient algorithm leveraging bad character and good suffix heuristics.

```c

int bruteFS1(const char *text, int n, const char *pattern, int m);

int bruteFS2(const char *text, int n, const char *pattern, int m);

int bruteFS3(char *text, int n, const char *pattern, int m);
int searchWithHelperFunc1(const char *text, int n, const char *pattern, int m);
int searchWithHelperFunc2(const char *text, int n, const char *pattern, int m);
int searchWithHelperFunc3(char *text, int n, const char *pattern, int m);
void mp(const char *text, int n, const char *pattern, int m);
void kmp(const char *text, int n, const char *pattern, int m);
void BM(const char *text, int n, const char *pattern, int m);
void horspool(const char *text, int n, const char *pattern, int m);
int quick_search(const char *text, const char *pattern);
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


#### Run the code

To run the hash table implementation :


```c

make trie_ht && ./trie_ht

```

To clean the project from executables :

```c

make clean

```



