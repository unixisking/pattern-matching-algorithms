#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int genRandomChar(int min, int max) { return rand() % (max + 1 - min) + min; }

void genAlphabet(int size, char alphabet[size]) {
  for (int i = 0; i < size; i++) {
    char newChar;
    int isUnique;

    do {
      isUnique = 1; // Supposons que le caractère est unique
      newChar = genRandomChar(33, 126);

      // Vérifions s'il existe déjà dans l'alphabet
      for (int j = 0; j < i; j++) {
        if (alphabet[j] == newChar) {
          isUnique = 0; // Pas unique, on doit générer un nouveau caractère
          break;
        }
      }
    } while (!isUnique);

    alphabet[i] = newChar; // Ajoutons le caractère unique à l'alphabet
  }
}

void generateText(int textLength, int alphabetSize,
                  char alphabet[alphabetSize]) {
  for (int i = 0; i < textLength; i++) {
    printf("%c", alphabet[rand() % alphabetSize]);
  }
  printf("\n");
}

void generateWordlist(int wordCount, int wordLength, int alphabetSize,
                      char alphabet[alphabetSize]) {
  for (int i = 0; i < wordCount; i++) {
    for (int j = 0; j < wordLength; j++) {
      printf("%c", alphabet[rand() % alphabetSize]);
    }
    printf("\n");
  }
}

void saveAlphabetToFile(const char *filename, int size, char alphabet[size]) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    perror("Error opening file");
    exit(1);
  }
  for (int i = 0; i < size; i++) {
    fputc(alphabet[i], file);
  }
  fclose(file);
}

void usage(const char *progName) {
  printf("Usage: %s -m <mode> -a <alphabet_size> [-l <word_length>] [-n "
         "<word_count>] [-i <alphabet_filepath>]\n",
         progName);
  printf("Modes:\n");
  printf("  g : Generate and save an alphabet to 'alphabet.txt'\n");
  printf("  w : Generate a wordlist using 'alphabet.txt'\n");
  exit(1);
}

void loadAlphabetFromFile(const char *filename, int size, char alphabet[size]) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(1);
  }
  for (int i = 0; i < size; i++) {
    alphabet[i] = fgetc(file);
  }
  fclose(file);
}

int main(int argc, char **argv) {
  srand(time(NULL)); // Seed the random number generator

  char mode = 0;
  char *alphabet_filepath = NULL;
  int alphabetSize = 0;
  int length = 0;
  int count = 0;

  int opt;
  while ((opt = getopt(argc, argv, "m:a:l:n:i:")) != -1) {
    switch (opt) {
    case 'm':
      mode = optarg[0];
      break;
    case 'a':
      alphabetSize = atoi(optarg);
      break;
    case 'l':
      length = atoi(optarg);
      break;
    case 'n':
      count = atoi(optarg);
      break;
    case 'i':
      alphabet_filepath = optarg;
      break;
    default:
      usage(argv[0]);
    }
  }

  if (!mode || alphabetSize <= 0 ||
      (mode == 'w' &&
       (length <= 0 || count <= 0 || alphabet_filepath == NULL)) ||
      (mode == 't' && (length <= 0 || alphabet_filepath == NULL))) {
    usage(argv[0]);
  }

  char alphabet[alphabetSize];
  switch (mode) {
  case 'g':
    genAlphabet(alphabetSize, alphabet);
    printf("%s", alphabet);
    break;
  case 'w':
    loadAlphabetFromFile(alphabet_filepath, alphabetSize, alphabet);
    generateWordlist(count, length, alphabetSize, alphabet);
    break;
  case 't':
    loadAlphabetFromFile(alphabet_filepath, alphabetSize, alphabet);
    generateText(length, alphabetSize, alphabet);
    break;
  default:
    usage(argv[0]);
  }

  return 0;
}