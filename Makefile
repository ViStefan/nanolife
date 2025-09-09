.PHONY: clean all test

vpath %.c src

INCLUDE += -I ./include
CFLAGS += -Wall -Wextra -Werror -pedantic -std=c99 $(INCLUDE)

all: brute_4x4 gentab permutate rotate

COMMON_FILES = johnson_trotter.c  map.c utils.c life.c pretty_print.c lookup_table.c args.c
BRUTE_FILES = 
GENTAB_FILES = 
PERMUTATE_FILES =
ROTATE_FILES =
 
brute_4x4: $(BRUTE_FILES) $(COMMON_FILES)

gentab: $(GENTAB_FILES) $(COMMON_FILES)

permutate: $(PERMUTATE_FILES) $(COMMON_FILES)

rotate: $(ROTATE_FILES) $(COMMON_FILES)

check:
	./test/smoke.sh

clean:
	rm brute_4x4 gentab permutate
