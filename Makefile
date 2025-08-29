.PHONY: clean all

all: brute_4x4 gentab permutate

brute_4x4: brute_4x4.c lookup_table.c johnson_trotter.c life.c map.c utils.c
	cc brute_4x4.c johnson_trotter.c lookup_table.c life.c map.c utils.c -o brute_4x4

gentab: gentab.c johnson_trotter.c pretty_print.c life.c map.c utils.c
	cc gentab.c johnson_trotter.c pretty_print.c life.c map.c utils.c -o gentab

permutate: permutate.c johnson_trotter.c utils.c
	cc permutate.c johnson_trotter.c utils.c -o permutate

clean:
	rm brute_4x4 gentab permutate
