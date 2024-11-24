/**
 * Generates a text of the specified size using the given alphabet size.
 * The generated text is stored in a file at the provided filepath.
 *
 * @param size The size of the text to generate (number of characters).
 * @param alphabetSize The number of unique characters in the alphabet to use.
 * @param filepath The path to the file where the generated text will be saved.
 */
void generateText(int size, int alphabetSize, const char *filepath);

/**
 * Generates a wordlist of the specified size using the given alphabet size.
 * The generated wordlist is stored in a file at the provided filepath.
 *
 * @param size The number of words to generate.
 * @param alphabetSize The number of unique characters in the alphabet to use
 * for the words.
 * @param filepath The path to the file where the generated wordlist will be
 * saved.
 */
void generateWordlist(int size, int alphabetSize, const char *filepath);
