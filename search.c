#include "search.h"
#include "limits.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bruteFS1(const char *text, int n, const char *pattern, int m) {
  for (int i = 0; i <= n - m; i++) {
    int j = 0;
    while (j <= m - 1 && pattern[j] == text[i + j]) {
      j++;
    }
    if (j == m) {
      return i;
    }
  }
  return -1;
}

int bruteFS2(const char *text, int n, const char *pattern, int m) {
  const char c = pattern[0];

  int i = 0;
  while (i <= n - m && text[i] != c) {
    i++;
  }

  while (i <= n - m) {
    int j = 0;
    while (j <= m - 1 && pattern[j] == text[i + j]) {
      j++;
    }
    if (j == m) {
      return i;
    }
    i++;
  }
  return -1;
}

// TODO: Ask about this:  how does a sentinelle make things better?
int bruteFS3(char *text, int n, const char *pattern, int m) {
  char *textWithSentinelle = realloc(text, sizeof(char) * (m + n + 1));
  if (textWithSentinelle == NULL) {
    free(text);
    return -1;
  }
  /* Add sentinelle at the end of the text */
  for (int i = n; i < n + m + 1; i++) {
    textWithSentinelle[i] = pattern[i - n];
  }
  const char c = pattern[0];

  int i = 0;
  n = strlen(textWithSentinelle);

  while (i <= n - m && textWithSentinelle[i] != c) {
    i++;
  }

  while (i <= n - m) {
    // bail if we reach sentinelle
    if (i == n - m) {
      return -1;
    }

    int j = 0;
    while (j <= m - 1 && pattern[j] == textWithSentinelle[i + j]) {
      j++;
    }
    if (j == m) {
      return i;
    }
    i++;
  }
  return -1;
}

int searchWithHelperFunc1(const char *text, int n, const char *pattern, int m) {
  for (int i = 0; i <= n - m; i++) {
    if (strncmp(text + i, pattern, m) == 0) {
      return i;
    }
  }
  return -1;
}

int searchWithHelperFunc2(const char *text, int n, const char *pattern, int m) {
  const char c = pattern[0];

  int i = 0;
  for (; i <= n - m && text[i] != c; i++)
    ;

  while (i <= n - m) {
    if (strncmp(text + i, pattern, m) == 0) {
      return i;
    }
    i++;
  }

  return -1;
}

int searchWithHelperFunc3(char *text, int n, const char *pattern, int m) {
  char *textWithSentinelle = realloc(text, sizeof(char) * (m + n + 1));
  if (textWithSentinelle == NULL) {
    free(text);
    return -1;
  }
  /* Add sentinelle at the end of the text */
  for (int i = n; i < n + m + 1; i++) {
    textWithSentinelle[i] = pattern[i - n];
  }
  const char c = pattern[0];

  int i = 0;
  n = strlen(textWithSentinelle);

  for (; i <= n - m && textWithSentinelle[i] != c; i++)
    ;

  while (i <= n - m) {
    if (i == n - m) {
      return -1;
    }
    if (strncmp(textWithSentinelle + i, pattern, m) == 0) {
      return i;
    }
    i++;
  }

  return -1;
}
void preprocessMp(const char *pattern, int m, int *shift_table) {
  int i = 0, j = shift_table[0] = -1;

  while (i < m) {
    while (j > -1 && pattern[i] != pattern[j]) {
      j = shift_table[j];
    }
    shift_table[++i] = ++j;
  }
}

void mp(const char *text, int n, const char *pattern, int m) {
  int i = 0, j = 0, shift_table[m];

  preprocessMp(pattern, m, shift_table);

  while (j < n) {
    while (i >= 0 && pattern[i] != text[j]) {
      i = shift_table[i];
    }
    i++;
    j++;
    if (i == m) {
      printf("found pattern at index = %d\n", j - i);
      i = shift_table[i];
    }
  }
}

void preprocessKmp(const char *pattern, int m, int *shift_table) {
  int i = 0, j = shift_table[0] = -1;

  while (i < m) {
    while (j > -1 && pattern[i] != pattern[j]) {
      j = shift_table[j];
    }
    i++;
    j++;
    if (pattern[i] == pattern[j]) {
      shift_table[i] = shift_table[j];
    } else {
      shift_table[i] = j;
    }
  }
}

void kmp(const char *text, int n, const char *pattern, int m) {
  int i = 0, j = 0, shift_table[m];

  preprocessKmp(pattern, m, shift_table);

  while (j < n) {
    while (i >= 0 && pattern[i] != text[j]) {
      i = shift_table[i];
    }
    i++;
    j++;
    if (i == m) {
      printf("found pattern at index = %d\n", j - i);
      i = shift_table[i];
    }
  }
}

void BMBadCharRule(const char *pattern, int m, int badMatchTable[]) {
  for (int i = 0; i < UCHAR_MAX; i++) {
    badMatchTable[i] = m;
  }
  for (int i = 0; i < m - 1; i++) {
    badMatchTable[(int)pattern[i]] = m - i - 1;
  }
}

void BMSuffixes(const char *pattern, int m, int suffixes[]) {
  int f, i;

  suffixes[m - 1] = m;
  int g = m - 1;

  for (i = m - 2; i >= 0; i--) {
    if (i > g && suffixes[i + m - 1 - f] < i - g) {
      suffixes[i] = suffixes[i + m - 1 - f];
    } else {
      if (i < g) {
        g = i;
      }
      f = i;
      // calc of suffix here
      while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
        g--;
      }
      suffixes[i] = f - g;
    }
  }
}

void BMGoodSuffix(const char *pattern, int m, int goodSuffixTable[]) {
  int suffixes[m];

  BMSuffixes(pattern, m, suffixes);

  for (int i = 0; i < m; i++) {
    goodSuffixTable[i] = m;
  }

  for (int i = m - 1; i >= 0; i--) {
    if (suffixes[i] == i + 1) {
      for (int j = 0; j < m - 1 - i; j++) {
        if (goodSuffixTable[j] == m) {
          goodSuffixTable[j] = m - 1 - i;
        }
      }
    }
  }
  for (int i = 0; i <= m - 2; ++i)
    goodSuffixTable[m - 1 - suffixes[i]] = m - 1 - i;
}

void BM(const char *text, int n, const char *pattern, int m) {
  if (m == 0 || n < m) {
    printf("Invalid pattern or text length.\n");
    return;
  }
  int i, j = m - 1, badCharRuleTable[UCHAR_MAX], goodSuffixTable[m];

  BMBadCharRule(pattern, m, badCharRuleTable);
  BMGoodSuffix(pattern, m, goodSuffixTable);

  while (j < n) {
    i = m - 1;
    while (i >= 0 && pattern[i] == text[j - m + 1 + i]) {
      i--;
    }
    if (i < 0) {
      printf("Found pattern %s in text at index: %d", pattern, j);
      j += goodSuffixTable[0];
    } else {
      j += MAX(goodSuffixTable[i],
               badCharRuleTable[(int)text[j - m + 1 + i]] - m + i + 1);
    }
  }
}

void horspool(const char *text, int n, const char *pattern, int m) {
  int badCharRuleTable[UCHAR_MAX];

  BMBadCharRule(pattern, m, badCharRuleTable);

  int j = 0;
  while (j <= n - m) {
    char firstChar = text[j + m - 1];
    if (pattern[m - 1] == firstChar && memcmp(pattern, text + j, m - 1) == 0) {
      printf("Found pattern in text at index: %d", j);
    }
    j += badCharRuleTable[(int)firstChar];
  }
}

void QSBadCharRule(const char *pattern, int m, int badMatchTable[]) {
  for (int i = 0; i < UCHAR_MAX; i++) {
    badMatchTable[i] = m + 1;
  }
  for (int i = 0; i < m; i++) {
    badMatchTable[(int)pattern[i]] = m - i;
  }
}

void quickSearch(const char *text, int n, const char *pattern, int m) {
  int badCharRuleTable[UCHAR_MAX];

  QSBadCharRule(pattern, m, badCharRuleTable);

  int j = 0;
  while (j <= n - m) {
    if (memcmp(pattern, text + j, m) == 0) {
      printf("Found pattern in text at index: %d", j);
    }
    j += badCharRuleTable[(int)text[m + j]];
  }
}

int main(int argc, char *argv[]) {
  char *text = malloc(sizeof(char) * 25);
  strcpy(text, "GCATCGCAGAGAGTATACAGTACG");
  // const char *text = "GCATCGCAGAGAGTATACAGTACG";
  const char *pattern = "GTATA";

  // printf("bruteForce: %d\n", bruteFS1(text, pattern));
  // printf("bruteForce: %d\n", searchWithHelperFunc1(text, pattern));

  int n = strlen(text);
  int m = strlen(pattern);
  printf("helperfunc: %d", searchWithHelperFunc3(text, n, pattern, m));

  quickSearch(text, n, pattern, m);

  return 0;
}