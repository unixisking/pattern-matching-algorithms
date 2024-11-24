#ifndef HEADER_SEARCH
#define HEADER_SEARCH

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/**
 *
 * Brute force algorithm, no fast loop & no sentinelle.
 */
int bruteFS1(const char *text, int n, const char *pattern, int m);
/**
 *
 * Brute force algorithm, with fast loop & no sentinelle.
 */
int bruteFS2(const char *text, int n, const char *pattern, int m);
/**
 *
 * Brute force algorithm, with fast loop & sentinelle.
 */
int bruteFS3(char *text, int n, const char *pattern, int m);

/**
 * Brute force algorithm, with strncmp, no fast loop
 */
int searchWithHelperFunc1(const char *text, int n, const char *pattern, int m);
/**
 * Brute force algorithm, with strncmp, with fast loop
 */
int searchWithHelperFunc2(const char *text, int n, const char *pattern,
                          int m);

/**
 * Brute force algorithm, with strncmp, with fast loop & sentinelle
 */
int searchWithHelperFunc3(char *text, int n, const char *pattern,
                          int m); // TODO

void mp(const char *text, int n, const char *pattern, int m);
void kmp(const char *text, int n, const char *pattern, int m);
void BM(const char *text, int n, const char *pattern, int m);
void horspool(const char *text, int n, const char *pattern, int m);
int quick_search(const char *text, const char *pattern); // TODO

#endif
