CC = gcc
CFLAGS = -I. -Wall -g
RM = rm -f
DEPS = trie_tm.h trie_ht.h

# Compiling to object files without linking
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

trie_tm: main_tm.o trie_tm.o
	$(CC) -o trie_tm main_tm.o trie_tm.o $(CFLAGS)

trie_ht: main_ht.o trie_ht.o
	$(CC) -o trie_ht main_ht.o trie_ht.o $(CFLAGS)

.PHONY: clean

clean:
	$(RM) *.o trie_tm trie_ht
