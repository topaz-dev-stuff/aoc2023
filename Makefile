# Definitions

CC = gcc
CC_FLAGS = -Iinclude 
CC_OPTIONS = -c
CC_SO_OPTIONS = -shared -fpic
CC_DL_OPTIONS = -rdynamic
RM = /bin/rm -f
MV = mv -f
LD = gcc
LIBS = -fopenmp

PUZZLE?=test

# Targets

all: sources clean
all_debug: debug clean

memcheck: all_debug
	valgrind --leak-check=full --track-origins=yes -s bin/runner input/${PUZZLE}.txt

gdb: all_debug
	gdb bin/runner

sources: CC_FLAGS += -O3 -march=native -ftree-vectorize -ftree-vectorizer-verbose=2
sources: 
	(cd src && make $@)
	${CC} ${CC_FLAGS} -o bin/runner src/aoc.c `/bin/ls src/util/*.o src/puzzles/${PUZZLE}.o` ${LIBS}

debug: CC_FLAGS += -O0 -Wall -ggdb
debug: 
	(cd src && make $@)
	${CC} ${CC_FLAGS} -o bin/runner src/aoc.c `/bin/ls src/util/*.o src/puzzles/${PUZZLE}.o`

clean:
	(cd src && make $@)
	${RM} *.o

tidy:
	${RM} bin/runner
