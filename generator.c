#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

int genRandomChar(int min, int max) { return rand() % (max + 1 - min) + min; }

void genAlphabet(int size, char alphabet[size]) {
  for (int i = 0; i < size; i++) {
    // ASCII printable characters 32-127
    alphabet[i] = genRandomChar(32, 127);
  }
}

void generateText(int size, int alphabetSize, char alphabet[alphabetSize],
                  char text[size]) {

  for (int i = 0; i < size; i++) {
    text[i] = alphabet[genRandomChar(0, alphabetSize - 1)];
  }
  text[size] = '\0';
}

void generateWordlist(int size, int alphabetSize, char alphabet[alphabetSize],
                      int wordLength, char wordList[size][wordLength + 1]) {

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < wordLength; j++) {
      wordList[i][j] = alphabet[genRandomChar(0, alphabetSize - 1)];
    }
    wordList[i][wordLength] = '\0';
  }
}

typedef struct Generator {
  char *kind;
  int size;
  int alphabetSize;
  int wordLength; // wordlist case
} Generator;

int main(int argc, char **argv) {

  Generator *gen = malloc(sizeof(Generator));
  if (gen == NULL) {
    perror("Error allocating memory for generator");
    exit(1);
  }

  gen->kind = NULL;
  gen->size = 0;
  gen->alphabetSize = 0;
  gen->wordLength = 0;

  int opt;
  while ((opt = getopt(argc, argv, "t:w:a:l:")) != -1) {
    switch (opt) {
    case 't':
      gen->kind = "text";
      if (optarg) {
        gen->size = atoi(optarg);

      } else {
        perror("Option -t requires a value");
        exit(1);
      }
      break;
    case 'w':
      gen->kind = "wordlist";
      if (optarg) {
        gen->size = atoi(optarg);

      } else {
        perror("Option -w requires a value");
        exit(1);
      }
      break;
    case 'a':
      if (optarg) {
        gen->alphabetSize = atoi(optarg);
      } else {
        perror("Option -a requires a value");
        exit(1);
      }
      break;
    case 'l':
      if (optarg) {
        gen->wordLength = atoi(optarg);
      } else {
        perror("Option -l requires a value");
        exit(1);
      }
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-t value] [-w value] [-ya]\n", argv[0]);
      exit(1);
    }
  }
  // Check if a kind was specified
  if (gen->kind == NULL) {
    fprintf(stderr, "You must specify a kind with -t or -w\n");
    free(gen);
    exit(1);
  }

  printf("Kind: %s\nSize: %d\nAlphabet Size: %d\nWord Length: %d\n", gen->kind,
         gen->size, gen->alphabetSize, gen->wordLength);

  free(gen);

  return 0;
}