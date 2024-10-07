CC = gcc
CFLAGS = -I.
RM = rm -f
OBJ = main.o trie-tm.o trie-hashtable.o
DEPS = trie-tm.h trie-hashtable.h

# Compiling to object files without linking
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

trie-tm: main.o trie-tm.o trie-hashtable.o
	$(CC) -o main main.o trie-tm.o $(CFLAGS)

trie-hashtable: main.o trie-hashtable.o
	$(CC) -o main main.o trie-hashtable.o $(CFLAGS)

.PHONY: clean

clean:
	$(RM) $(OBJ) main

