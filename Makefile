CC = gcc
CFLAGS = -I.
RM = rm -f
OBJ = tp1.o trie-tm.o trie-hashtable.o
DEPS = trie-tm.h trie-hashtable.h

# Compiling to object files without linking
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tp1: tp1.o trie-tm.o trie-hashtable.o
	$(CC) -o tp1 tp1.o trie-tm.o trie-hashtable.o $(CFLAGS)

.PHONY: clean

clean:
	$(RM) $(OBJ) tp1

