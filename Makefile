.PHONY: clean all test

all: brute_4x4 gentab permutate

brute_4x4: src/brute_4x4.c src/lookup_table.c src/johnson_trotter.c src/life.c src/map.c src/utils.c
	cc -Wall -Wextra -Werror -pedantic -std=c99 -I ./include src/brute_4x4.c src/johnson_trotter.c src/lookup_table.c src/life.c src/map.c src/utils.c -o brute_4x4

gentab: src/gentab.c src/johnson_trotter.c src/pretty_print.c src/life.c src/map.c src/utils.c
	cc -Wall -Wextra -Werror -pedantic -std=c99 -I ./include src/gentab.c src/johnson_trotter.c src/pretty_print.c src/life.c src/map.c src/utils.c -o gentab

permutate: src/permutate.c src/johnson_trotter.c src/utils.c
	cc -Wall -Wextra -Werror -pedantic -std=c99 -I ./include src/permutate.c src/johnson_trotter.c src/utils.c -o permutate

test:
	./test/smoke.sh

clean:
	rm brute_4x4 gentab permutate
