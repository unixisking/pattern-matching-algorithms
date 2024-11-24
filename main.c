#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRIE_ALPHABET_SIZE_OPTION 299
#define TRIE_TEXT_SIZE_OPTION 300
#define TRIE_MAXNODE 301
#define TRIE_WORLDLIST 302

const char *argp_program_version = "tp2 1.0";
const char *argp_program_bug_address = "<sidahmed-brahimi@univ-rouen.fr>";

// Structure to hold parsed arguments for algorithm execution
struct AlgoArgs {
  char *name;        // Algorithm name
  int alphabet_size; // Size of the alphabet
  int text_size;     // Size of the text
  char *output_file; // Output file path
};

// Structure to hold parsed arguments for data structure (Trie) implementation
struct DSImplArgs {
  char *name;      // Data structure name
  char **wordList; // List of words to be used
  int maxNode;     // Maximum number of nodes
};

/*
 * Main structure to manage parsed arguments
 * - `algo` is used when the program runs with the `-a` option (algorithm
 * execution).
 * - `ds` is used when the program runs with `-t` or `-T` options (Trie
 * implementations).
 *
 * Note:
 * - If the user chooses to execute an algorithm (`-a`), then `ds` will be NULL.
 * - Conversely, if the user opts for data structure operations (`-t` or `-T`),
 * then `algo` will be NULL.
 */
struct Arguments {
  struct AlgoArgs *algo; // Pointer to algorithm arguments (if applicable)
  struct DSImplArgs *ds; // Pointer to data structure arguments (if applicable)
};

// Argument parsing function
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct Arguments *arguments = state->input;

  // printf("parse_opt: key = %c arg = %s \n", key, arg);

  switch (key) {
  case 'a': // Algorithm
    arguments->algo = malloc(sizeof(struct AlgoArgs));
    if (arguments->algo == NULL) {
      perror("Error allocating memory to program arguments");
      exit(1);
    }
    arguments->algo->name = arg;
    break;
  case TRIE_ALPHABET_SIZE_OPTION: // Alphabet size
    // arguments->alphabet_size = atoi(arg);
    arguments->algo->alphabet_size = atoi(arg);
    break;
  case TRIE_TEXT_SIZE_OPTION: // Text size
    // arguments->text_size = atoi(arg);
    arguments->algo->text_size = atoi(arg);
    break;
  case 'o': // Output file
    arguments->algo->output_file = arg;
    break;
  case ARGP_KEY_END: // Post-parsing validation
    if (arguments->algo) {
      if (arguments->algo->name != NULL) {
        if (arguments->algo->alphabet_size == 0) {
          argp_error(state, "The 'boyer-moore' algorithm requires "
                            "--alphabet-size to be specified.");
        }
        if (arguments->algo->text_size == 0) {
          argp_error(state, "The 'boyer-moore' algorithm requires --text-size "
                            "to be specified.");
        }
      }
    }

    else {
      argp_error(state, "You must specify an algorithm with -a.");
    }
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static char doc[] = "TP-2";

enum {
  GROUP_ALGO = 1, // Group for algorithm options (-a, --alphabet-size, etc.)
  GROUP_DS        // Group for data structure options (-t, -T, --max-node, etc.)
};

static struct argp_option options[] = {
    // Algorithm related options (-a)
    {"algorithm", 'a', "ALGO", 0,
     "Algorithm to use (horspool, boyer-moore, bf{0..6}, mp, kmp)", GROUP_ALGO},
    {"alphabet-size", 299, "SIZE", 0, "Alphabet size for the algorithm",
     GROUP_ALGO},
    {"text-size", 300, "SIZE", 0, "Size of the text input", GROUP_ALGO},
    {"output", 'o', "FILE", 0, "Output file for the results", GROUP_ALGO},

    // Data structure related options (-t and -T)
    {"hashtable", 't', NULL, 0,
     "Use hashtable-based implementation (implies name='hashtable')", GROUP_DS},
    {"transition-table", 'T', NULL, 0,
     "Use transition table-based implementation (implies "
     "name='transition-table')",
     GROUP_DS},
    {"max-node", 301, "COUNT", 0,
     "Maximum number of nodes (for Trie implementations)", GROUP_DS},
    {"word-list", 302, "FILE", 0, "File containing list of words", GROUP_DS},

    {0}};

// Argp parser setup
static struct argp argp = {options, parse_opt, NULL, doc};

int main(int argc, char **argv) {
  // struct arguments arguments = {NULL, 0, 0, NULL};
  struct Arguments arguments = {NULL, NULL};

  // Parse arguments
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  // Display parsed arguments
  printf("Algorithm: %s\n", arguments.algo->name);
  printf("Alphabet Size: %d\n", arguments.algo->alphabet_size);
  printf("Text Size: %d\n", arguments.algo->text_size);
  if (arguments.algo->output_file) {
    printf("Output File: %s\n", arguments.algo->output_file);
  }

  return 0;
}
