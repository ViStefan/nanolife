
brute_4x4: brute_4x4.c lookup_table.c johnson_trotter.c life.c map.c
	cc brute_4x4.c johnson_trotter.c lookup_table.c life.c map.c -o brute_4x4

gentab: gentab.c johnson_trotter.c pretty_print.c life.c map.c
	cc gentab.c johnson_trotter.c pretty_print.c life.c map.c -g -o gentab

permutate: permutate.c johnson_trotter.c
	cc permutate.c johnson_trotter.c -g -o permutate
