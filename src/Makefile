
sources: CC_FLAGS += -O3 -march=native -ftree-vectorize -ftree-vectorizer-verbose=2
sources: 
	(cd puzzles && make $@)
	(cd util && make $@)

debug: CC_FLAGS += -O0 -Wall -ggdb
debug: 
	(cd puzzles && make $@)
	(cd util && make $@)

clean:
	(cd puzzles && make $@)
	(cd util && make $@)
	${RM} *.o