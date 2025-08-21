
brute_4x4: brute_4x4.c gentab.c johnson_trotter.c
	cc brute_4x4.c johnson_trotter.c gentab.c -o brute_4x4

gentab: gentab.c
	cc gentab.c -g -o gentab

johnson: johnson_trotter.c
	cc johnson_trotter.c -g -o johnson_trotter
