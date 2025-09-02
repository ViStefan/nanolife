.PHONY: clean all test

vpath %.c src

INCLUDE += -I ./include
CFLAGS += -Wall -Wextra -Werror -pedantic -std=c99 $(INCLUDE)

all: brute_4x4 gentab permutate

COMMON_FILES = map.c utils.c
BRUTE_FILES = lookup_table.c johnson_trotter.c life.c 
GENTAB_FILES = johnson_trotter.c pretty_print.c life.c
PERMUTATE_FILES = johnson_trotter.c
 
brute_4x4: $(BRUTE_FILES) $(COMMON_FILES)

gentab: $(GENTAB_FILES) $(COMMON_FILES)

permutate: $(PERMUTATE_FILES) $(COMMON_FILES)

check:
	./test/smoke.sh

clean:
	rm brute_4x4 gentab permutate
