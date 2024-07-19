CFLAGS = -g -O3 -std=c17 -march=native
WFLAGS = -Wall -Wextra -Wshadow -pedantic

DIR_SRC = src
DIR_TEST = tests

SRCS = $(shell find $(DIR_SRC) -type f -iname '*.c')
OBJS = $(SRCS:.c=.o)

TESTS = $(shell find $(DIR_TEST) -type f -iname '*.c')
TOBJS = $(TESTS:.c=.o)

.build: $(OBJS)
.build_test: $(TOBJS)

all: .build
	gcc $(CFLAGS) $(WFLAGS) -o sandsim bin/main.c $(OBJS) -lSDL2

test: .build .build_test
	gcc $(CFLAGS) $(WFLAGS) -Isrc -o testrunner $(OBJS) $(TOBJS) -lcriterion 

clean:
	rm -f sandsim
