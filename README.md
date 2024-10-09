# Transition table based Trie Data Structure

This repository contains an implementation of a **Trie** (prefix tree) in C, a data structure used to store and search strings efficiently, especially useful in applications like autocomplete, spell-check, or dictionary implementation.

## Features

- **Insert words** into the Trie.
- **Search words** to check their existence in the Trie.
- Efficient memory usage with a transition matrix.

## Project Structure

- `trie-tm.h`: Header file containing Trie structure definitions and function prototypes.
- `trie-tm.c`: Source file with function implementations for the Trie operations.
- `main_tm.c`: Example usage and test cases for the Trie functions as well the following functions: insertPrefix, insertSuffix, insertFactors

## Trie Data Structure

The core structure is defined as follows:

```c
struct _trie {
    int maxNode;        // Maximum number of nodes
    int nextNode;       // Next available node index
    int **transitions;  // Transition matrix storing connections between nodes
    char *finite;       // Array indicating which nodes are end-of-word states
};

typedef struct _trie *Trie;


## Usage

To run the program, please use the following command:


```c

make trie_tm && ./trie_tm

```

