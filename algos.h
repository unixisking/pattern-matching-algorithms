#ifndef HEADER_SEARCH
#define HEADER_SEARCH

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/**
 * Brute force string search algorithm without optimization:
 * No fast loop and no sentinelle used for early termination.
 *
 * @param text The text to search in.
 * @param n The length of the text.
 * @param pattern The pattern to search for.
 * @param m The length of the pattern.
 * @return The starting index of the first occurrence of the pattern in the
 * text, or -1 if not found.
 */
void bruteFS1(const char *text, int n, const char *pattern, int m);

/**
 * Brute force string search algorithm with fast loop optimization:
 * Improves the loop iteration speed but does not use a sentinelle.
 *
 * @param text The text to search in.
 * @param n The length of the text.
 * @param pattern The pattern to search for.
 * @param m The length of the pattern.
 * @return The starting index of the first occurrence of the pattern in the
 * text, or -1 if not found.
 */
void bruteFS2(const char *text, int n, const char *pattern, int m);

/**
 * Brute force string search algorithm with both fast loop and sentinelle:
 * Adds a sentinelle to optimize early termination of the search.
 *
 * @param text The text to search in.
 * @param n The length of the text.
 * @param pattern The pattern to search for.
 * @param m The length of the pattern.
 * @return The starting index of the first occurrence of the pattern in the
 * text, or -1 if not found.
 */
void bruteFS3(char *text, int n, const char *pattern, int m);

/**
 * Brute force string search algorithm using strncmp:
 * No fast loop is applied for optimization.
 *
 * @param text The text to search in.
 * @param n The length of the text.
 * @param pattern The pattern to search for.
 * @param m The length of the pattern.
 * @return The starting index of the first occurrence of the pattern in the
 * text, or -1 if not found.
 */
void searchWithHelperFunc1(const char *text, int n, const char *pattern, int m);

/**
 * Brute force string search algorithm using strncmp:
 * Applies a fast loop for better performance.
 *
 * @param text The text to search in.
 * @param n The length of the text.
 * @param pattern The pattern to search for.
 * @param m The length of the pattern.
 * @return The starting index of the first occurrence of the pattern in the
 * text, or -1 if not found.
 */
void searchWithHelperFunc2(const char *text, int n, const char *pattern, int m);

/**
 * Brute force string search algorithm using strncmp:
 * Combines both fast loop and sentinelle for improved performance.
 *
 * @param text The text to search in.
 * @param n The length of the text.
 * @param pattern The pattern to search for.
 * @param m The length of the pattern.
 * @return The starting index of the first occurrence of the pattern in the
 * text, or -1 if not found.
 */
void searchWithHelperFunc3(char *text, int n, const char *pattern, int m);

/**
 * Implements the Morris-Pratt (MP) algorithm for string matching:
 * Uses a prefix function for efficient searching.
 *
 * @param text The text to search in.
 * @param n The length of the text.
 * @param pattern The pattern to search for.
 * @param m The length of the pattern.
 */
void mp(const char *text, int n, const char *pattern, int m);

/**
 * Implements the Knuth-Morris-Pratt (KMP) algorithm for string matching:
 * Builds on the MP algorithm with optimized prefix matching.
 *
 * @param text The text to search in.
 * @param n The length of the text.
 * @param pattern The pattern to search for.
 * @param m The length of the pattern.
 */
void kmp(const char *text, int n, const char *pattern, int m);

/**
 * Implements the Boyer-Moore (BM) algorithm for string matching:
 * Utilizes the bad character and good suffix heuristics for efficiency.
 *
 * @param text The text to search in.
 * @param n The length of the text.
 * @param pattern The pattern to search for.
 * @param m The length of the pattern.
 */
void BM(const char *text, int n, const char *pattern, int m);

/**
 * Implements the Horspool algorithm for string matching:
 * A simplified version of Boyer-Moore focusing on the bad character heuristic.
 *
 * @param text The text to search in.
 * @param n The length of the text.
 * @param pattern The pattern to search for.
 * @param m The length of the pattern.
 */
void horspool(const char *text, int n, const char *pattern, int m);

/**
 * Implements the Quick Search algorithm for string matching:
 * Uses the bad character heuristic.
 *
 * @param text The text to search in.
 * @param n The length of the text.
 * @param pattern The pattern to search for.
 * @param m The length of the pattern.
 * @return The starting index of the first occurrence of the pattern in the
 * text, or -1 if not found.
 */
void quickSearch(const char *text, int n, const char *pattern, int m);

#endif
