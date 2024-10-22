#include <stdio.h>
#include <string.h>
#include "search.h"

int bruteFS1(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    for(int i = 0; i <= n - m; i++) {
        int j = 0;
        while(j <= m - 1 && pattern[j] == text[i+j]) {
            j++;
        }
        if(j == m) {
            return i;
        }
    }
    return -1;
}

int bruteFS2(const char*text, const char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    const char c = pattern[0];

    int i = 0;
    while(i <= n - m && text[i] != c) {
        i++;
    }

    while(i <= n - m) {
        int j = 0;
        while(j <= m - 1 && pattern[j] == text[i+j]) {
            j++;
        }
        if(j == m) {
            return i;
        }
        i++;
    }
    return -1;
}

int searchWithHelperFunc1(const char*text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);


    return strncmp(pattern, text, m);





}
int searchWithHelperFunc2(const char*text, const char *pattern){
    int n = strlen(text);
    int m = strlen(pattern);

    const char c = pattern[0];

    int i = 0;
    while(i <= n - m && text[i] != c) {
        i++;
    }

    return -1;

}

int mp(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    // Pre-processing: construct bonPref table

    // Double loop: use bonPref table to skip comparaisons

}

int kmp(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    // Pre-processing: construct MeilPref table

    // Double loop: use bonPref table to skip comparaisons

}
int main() {

    const char *text = "abcabcbabcabcabcaa";
    const char *pattern = "bcaa";

    // printf("bruteForce: %d\n", bruteFS1(text, pattern));
    printf("bruteForce: %d\n", searchWithHelperFunc1(text, pattern));

    
    return 0;
}