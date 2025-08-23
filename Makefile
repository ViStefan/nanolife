
brute_4x4: brute_4x4.c gentab.c johnson_trotter.c life.c map.c
	cc brute_4x4.c johnson_trotter.c gentab.c life.c map.c -o brute_4x4

gentab: gentab.c
	cc gentab.c -g -o gentab

permutate: permutate.c johnson_trotter.c
	cc permutate.c johnson_trotter.c -g -o permutate
