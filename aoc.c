/* This is the main runner suite for all aoc puzzles.
 * Each puzzle must implement a solve() function to complete parts
 * 1 and 2 of the puzzle and output any results.
 * The input file must be passed in as the first command-line argument.
 */

#include "util.h"

extern void solve(void *data, size_t len);

int main (int argc, char **argv) {
    void *data = NULL;
    struct stat stbuf;
    data = map_input(argv[1], &stbuf);
    if (data) {
        solve(data, stbuf.st_size);
    }
    else {
        perror("Error mapping input file");
        exit(EXIT_FAILURE);
    }
    if (munmap(data,stbuf.st_size) == -1) {
        perror("Error unmapping input file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
