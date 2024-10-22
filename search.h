#ifndef HEADER_SEARCH
#define HEADER_SEARCH


/**
 * 
 * Brute force algorithm, no fast loop & no sentinelle.
 */
int bruteFS1(const char *text, const char *pattern);
/**
 * 
 * Brute force algorithm, with fast loop & no sentinelle.
 */
int bruteFS2(const char *text, const char *pattern);
/**
 * 
 * Brute force algorithm, with fast loop & sentinelle.
 */
int bruteFS3(const char *text, const char *pattern);

/**
 * Brute force algorithm, with strncmp, no fast loop
 */
int searchWithHelperFunc1(const char*text, const char *pattern);
/**
 * Brute force algorithm, with strncmp, with fast loop
 */
int searchWithHelperFunc2(const char*text, const char *pattern);

int mp(const char *text, const char *pattern);
int kmp(const char *text, const char *pattern);
int boyer_moore(const char *text, const char *pattern);
int harspool(const char *text, const char *pattern);
int quick_search(const char *text, const char *pattern);

#endif