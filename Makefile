all: boggle.c linkedlist.c trie.c hashset.c
	gcc -g -Wall -o boggle boggle.c linkedlist.c trie.c hashset.c

clean:
	$(RM) boggle