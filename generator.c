
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main() {
  int size = 100;
  int alphabetSize = 3;
  int wordLength = 3;
  char wordList[size][wordLength + 1];

  char alphabet[alphabetSize];
  int textSize = 100;
  char text[textSize];

  srand((unsigned int)time((NULL)));

  genAlphabet(alphabetSize, alphabet);
  generateWordlist(size, alphabetSize, alphabet, wordLength, wordList);
  generateText(textSize, alphabetSize, alphabet, text);

  printf("print wordlist \n");
  for (int i = 0; i < size; i++) {
    printf("Word %d: %s\n", i + 1, wordList[i]);
  }

  printf("printing text\n");
  for (int i = 0; i < size; i++) {
    printf("%c", text[i]);
  }
  return 0;
}
