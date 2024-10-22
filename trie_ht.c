#include "trie_ht.h"
#include "limits.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Hashes a state and a letter to a number between 0 and M */
int hash_function(int state, unsigned char c, int maxNode) {
  int m = maxNode * MAX_NODE_MULTIPLIER;
  int prime = 31;
  return (state * prime + c) % m;
}

Trie createTrie(int maxNode) {
  /* 
   * maxTransitions is M: the maximum amount of space to hold transitions
   * MAX_NODE_MULTIPLIER: is a constant set to 3 chosen to reduce the number of collisions.
   * */
  int maxTransitions = maxNode * MAX_NODE_MULTIPLIER;

  Trie trie = malloc(sizeof(struct _trie));
  if (trie == NULL) {
    return NULL;
  }

  trie->maxNode = maxNode;
  trie->nextNode = 0;
  trie->transitions = malloc(sizeof(List) * maxTransitions);

  if (trie->transitions == NULL) {
    free(trie);
    return NULL;
  }

  for (int i = 0; i < maxTransitions; i++) {
    trie->transitions[i] = NULL;
  }

  trie->finite = malloc(sizeof(char) * maxNode);

  if (trie->finite == NULL) {
    free(trie->transitions);
    free(trie);
    return NULL;
  }

  for (int i = 0; i < maxNode; i++) {
    trie->finite[i] = 0;
  }

  return trie;
}

void insertInTrie(Trie trie, unsigned char *w) {
  if (trie == NULL) {
    return;
  }

  int currentState = 0;
  for (unsigned char *currentChar = w; *currentChar != '\0'; currentChar++) {
    int hash = hash_function(currentState, *currentChar, trie->maxNode);

    /* No hash collision: allocate List for transition */
    if (trie->transitions[hash] == NULL) {
      trie->transitions[hash] = malloc(sizeof(List));
      *trie->transitions[hash] = NULL;
    }

    List currentNode = *trie->transitions[hash];
    /* prevNode is used in the case where we reached the end of the LinkedList without finding the transition */
    List prevNode = NULL;
    /*
     * Here we are using transitionFound to check for a transition with the same startNode and letter
     * if a transition exist we set it to 1 and therefore skip adding the character
     * If a transition is not found then: we allocate memory for a new node and add it 
     *
     * */
    int transitionFound = 0;

    while (currentNode != NULL) {
      /*
       * When encountering a char that was already added
       * with the same state then skip creation of newNode
       * */

      if (currentNode->letter == *currentChar &&
          currentState == currentNode->startNode) {
        transitionFound = 1;
        currentState = currentNode->targetNode;
        break;
      }
      prevNode = currentNode;
      currentNode = currentNode->next;
    }
    if (transitionFound == 0) {
      List newNode = malloc(sizeof(struct _list));

      newNode->startNode = currentState;
      newNode->letter = *currentChar;
      newNode->targetNode = ++trie->nextNode;
      newNode->next = NULL;

      if (prevNode == NULL) {
        *trie->transitions[hash] = newNode;
      } else {
        prevNode->next = newNode;
      }
      currentState = newNode->targetNode;
    }
  }
  trie->finite[currentState] = 1;
}

int isInTrie(Trie trie, unsigned char *w) {

  /*
   * Check if the word is Empty
   */
  if (trie == NULL || *w == '\0') {
    return 0;
  }

  int state = 0;
  for (unsigned char *c = w; *c != '\0'; c++) {

    int hash = hash_function(state, *c, trie->maxNode);

    if (trie->transitions[hash] != NULL) {
      List currentNode = *trie->transitions[hash];

      /* If a transition is found then we traverse the linked list until we find the right char */
      while (currentNode != NULL) {
        if (currentNode->letter == *c) {
          state = currentNode->targetNode;
          break; // When the char is found, we break out of the loop and move on to the next one 
        } else {
          currentNode = currentNode->next;
        }
      }
      if (currentNode == NULL) {
        return 0;
      }
    } else {
      return 0;
    }
  }
  return trie->finite[state] == 1 ? 1 : 0;
}
