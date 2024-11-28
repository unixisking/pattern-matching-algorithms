#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFromFile(char *fileName, char *text) {
  FILE *file= fopen(fileName, "r");
  if (file == NULL) {
    printf("File could not be opened\n");
    exit(1);
  }

  for(int i = 0; i < 500000; i++) {
    text[i] = fgetc(file);
  }
  fclose(file);
}

int main(int argc, char **argv) {
  char opt;
  char *algoType = NULL;
  char *textFilepath = NULL;
  char *wordlistFilepath = NULL;

  while((opt = getopt(argc, argv, "a:t:w:")) != -1) {
    switch(opt) {
      case 'a':
        algoType = optarg;
        break;
      case 't':
        textFilepath = optarg;
        break;
      case 'w':
       wordlistFilepath = optarg;
       break;
      default:
        printf("Unknown option '%c'\n", optopt);
        break;
    }
  }

  printf("Algo Type: %s\n", algoType);
  printf("Text FilePath: %s\n", textFilepath);
  printf("Word List FilePath: %s\n", wordlistFilepath);

  if(textFilepath == NULL || wordlistFilepath == NULL || algoType == NULL) {
    printf("No enough arguments were provided\n");
    return 1;
  }

  char *text = malloc(sizeof(char) * 500000);
  if(text == NULL) {
    printf("Memory could not be allocated\n");
    return 1;
  }
  readFromFile(textFilepath, text);

  for(int i = 0; i < 5000; i++) {
    printf("%c", text[i]);
  }
  free(text);
  return 0;
}
