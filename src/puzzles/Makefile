# Definitions
CC = gcc
CC_FLAGS = -I../../include
CC_OPTIONS = -c 
CC_SO_OPTIONS = -shared -fpic
CC_DL_OPTIONS = -rdynamic
RM = /bin/rm -f
MV = mv -f
LD = gcc
LIBS = -fopenmp -lz

SRCS := test.c trebuchet.c cubes.c gears.c cards.c \
seeds.c
OBJS := $(SRCS:%.c=%.o)

# Generic rules

%.o: %.c
	${CC} ${CC_OPTIONS} ${CC_FLAGS} $<

# Targets

all: sources

sources: CC_FLAGS += -O3 -fopenmp -march=native -ftree-vectorize -ftree-vectorizer-verbose=2
sources: ${OBJS}

debug: CC_FLAGS += -Wall -ggdb
debug: ${OBJS}

clean:
	${RM} *.o
