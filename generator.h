/**
 * Generates a random character within the specified range [min, max].
 *
 * @param min The minimum value of the character range (inclusive).
 * @param max The maximum value of the character range (inclusive).
 * @return A randomly generated character within the specified range.
 */
int genRandomChar(int min, int max);

/**
 * Generates an alphabet of the specified size using characters within the
 * printable range (32-127).
 *
 * @param size The size of the alphabet to generate (number of unique
 * characters).
 * @param alphabet The array where the generated alphabet will be stored.
 */
void genAlphabet(int size, char alphabet[size]);

/**
 * Generates a text of the specified size using the given alphabet.
 * The generated text is stored in the provided array.
 *
 * @param size The size of the text to generate (number of characters).
 * @param alphabetSize The number of unique characters in the alphabet to use.
 * @param alphabet The array of characters representing the alphabet.
 * @param text The array where the generated text will be stored.
 */
void generateText(int size, int alphabetSize, char alphabet[alphabetSize],
                  char text[size]);

/**
 * Generates a wordlist of the specified size and word length using the given
 * alphabet. The generated wordlist is stored in the provided 2D array.
 *
 * @param size The number of words to generate.
 * @param alphabetSize The number of unique characters in the alphabet to use
 *                     for the words.
 * @param alphabet The array of characters representing the alphabet.
 * @param wordLength The length of each word to generate.
 * @param wordList The 2D array where the generated wordlist will be stored.
 *                 Each word is stored as a row, and all words are
 * null-terminated.
 */
void generateWordlist(int size, int alphabetSize, char alphabet[alphabetSize],
                      int wordLength, char wordList[size][wordLength + 1]);
