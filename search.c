#include "algos.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef void (*SearchAlgo)(const char *text, int n, const char *pattern, int m);

void measureExecutionTime(const char *text, int n, int wordlistLength, int m,
                          char **wordlist, SearchAlgo algo,
                          float metrics[wordlistLength]) {
  for (int i = 0; i < wordlistLength; i++) {
    clock_t start = clock();
    algo(text, n, wordlist[i], m);
    clock_t end = clock();
    metrics[i] = (float)(end - start) / CLOCKS_PER_SEC;
  }
}

void readTextFromFile(char *filepath, int n, char *text) {
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    printf("File could not be opened\n");
    exit(1);
  }

  for (int i = 0; i < n; i++) {
    text[i] = fgetc(file);
  }
  fclose(file);
}

void readWordListFromFile(char *filepath, int m, char **wordlist) {
  char word[m];
  FILE *file = fopen(filepath, "r");

  if (file == NULL) {
    printf("File could not be opened\n");
    free(wordlist);
    exit(1);
  }

  int i = 0;
  while (fscanf(file, "%99s", word) == 1) {
    wordlist[i] = malloc(sizeof(char) * strlen(word) + 1);
    if (wordlist[i] == NULL) {
      perror("Error allocating memory for word");
      break;
    }

    strcpy(wordlist[i], word);
    i++;
  }

  fclose(file);
}

int main(int argc, char **argv) {
  char opt;
  char *text;
  char **wordlist;
  char *algoType = NULL;
  char *textFilepath = NULL;
  char *wordlistFilepath = NULL;
  int m = 0;
  int wordlistLength = 100;
  int n = 500000;

  while ((opt = getopt(argc, argv, "a:t:w:m:")) != -1) {
    switch (opt) {
    case 'a':
      algoType = optarg;
      break;
    case 't':
      textFilepath = optarg;
      break;
    case 'w':
      wordlistFilepath = optarg;
      break;
    case 'm':
      m = atoi(optarg);
      break;
    default:
      printf("Unknown option '%c'\n", optopt);
      break;
    }
  }
  // printf("Algo Type: %s\n", algoType);
  // printf("Text FilePath: %s\n", textFilepath);
  // printf("Word List FilePath: %s\n", wordlistFilepath);
  // printf("Word length : %d\n", m);

  if (textFilepath == NULL || wordlistFilepath == NULL || algoType == NULL ||
      m == 0) {
    printf("No enough arguments were provided\n");
    return 1;
  }

  text = malloc(sizeof(char) * n);
  wordlist = malloc(sizeof(char *) * wordlistLength);
  if (text == NULL || wordlist == NULL) {
    printf("Memory could not be allocated\n");
    return 1;
  }
  readTextFromFile(textFilepath, n, text);
  readWordListFromFile(wordlistFilepath, m, wordlist);

  float metrics[wordlistLength];
  if (strcmp(algoType, "bm") == 0) {
    measureExecutionTime(text, n, wordlistLength, m, wordlist, BM, metrics);
  } else if (strcmp(algoType, "hp") == 0) {
    measureExecutionTime(text, n, wordlistLength, m, wordlist, horspool,
                         metrics);
  } else if (strcmp(algoType, "qs") == 0) {
    measureExecutionTime(text, n, wordlistLength, m, wordlist, quickSearch,
                         metrics);
  } else if (strcmp(algoType, "kmp") == 0) {
    measureExecutionTime(text, n, wordlistLength, m, wordlist, mp, metrics);
  } else if (strcmp(algoType, "mp") == 0) {
    measureExecutionTime(text, n, wordlistLength, m, wordlist, mp, metrics);
  } else if (strcmp(algoType, "hf3") == 0) {
    for (int i = 0; i < wordlistLength; i++) {
      clock_t start = clock();
      searchWithHelperFunc3(text, n, wordlist[i], m);
      clock_t end = clock();
      metrics[i] = (float)(end - start) / CLOCKS_PER_SEC;
    }
  }

  else if (strcmp(algoType, "hf2") == 0) {
    measureExecutionTime(text, n, wordlistLength, m, wordlist,
                         searchWithHelperFunc2, metrics);
  } else if (strcmp(algoType, "hf1") == 0) {
    measureExecutionTime(text, n, wordlistLength, m, wordlist,
                         searchWithHelperFunc1, metrics);
  } else if (strcmp(algoType, "bf3") == 0) {
    for (int i = 0; i < wordlistLength; i++) {
      clock_t start = clock();
      bruteFS3(text, n, wordlist[i], m);
      clock_t end = clock();
      metrics[i] = (float)(end - start) / CLOCKS_PER_SEC;
    }
  } else if (strcmp(algoType, "bf2") == 0) {
    measureExecutionTime(text, n, wordlistLength, m, wordlist, bruteFS2,
                         metrics);
  } else if (strcmp(algoType, "bf1") == 0) {
    measureExecutionTime(text, n, wordlistLength, m, wordlist, bruteFS1,
                         metrics);
  } else {
    printf("Error, unknown algo");
    exit(1);
  }
  float sum = 0;
  for (int i = 0; i < wordlistLength; i++) {
    sum += metrics[i];
  }
  printf("%.6f", sum / wordlistLength);

  free(text);
  for (int i = 0; i < wordlistLength; i++) {
    free(wordlist[i]);
  }
  free(wordlist);
  return 0;
}
