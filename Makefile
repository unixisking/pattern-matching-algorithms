CC = gcc
CFLAGS = -I.
RM = rm -f
OBJ = tp1.o trie-tm.o trie-hashtable.o search.o
DEPS = trie-tm.h trie-hashtable.h search.h

# Compiling to object files without linking
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tp1-tm: tp1.o trie-tm.o trie-hashtable.o
	$(CC) -o tp1 tp1.o trie-tm.o trie-hashtable.o $(CFLAGS)

tp1-hashtable: tp1.o trie-hashtable.o
	$(CC) -o tp1 tp1.o trie-hashtable.o $(CFLAGS)

search: search.o
	$(CC) -o search search.o $(CFLAGS)

.PHONY: clean

clean:
	$(RM) $(OBJ) tp1

