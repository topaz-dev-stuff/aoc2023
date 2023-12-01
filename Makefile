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

DAY?=test

# Targets

all: sources clean
all_debug: debug clean

memcheck: all_debug
	valgrind --leak-check=full --track-origins=yes -s ./runner input/${DAY}.txt

gdb: all_debug
	gdb runner

# install:
# 	chmod +x install.sh
# 	./install.sh

sources: CC_FLAGS += -O3 -march=native -ftree-vectorize -ftree-vectorizer-verbose=2
sources: 
	(cd puzzles && make $@)
	(cd util && make $@)
	${CC} ${CC_FLAGS} -o runner aoc.c `/bin/ls util/*.o puzzles/${DAY}.o` ${LIBS}

debug: CC_FLAGS += -O0 -Wall -ggdb
debug: 
	(cd puzzles && make $@)
	(cd util && make $@)
	${CC} ${CC_FLAGS} -o runner aoc.c `/bin/ls util/*.o puzzles/${DAY}.o`

clean:
	(cd puzzles && make $@)
	(cd util && make $@)
	${RM} *.o

tidy:
	${RM} runner
