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
    int status;

    struct timespec start, end;
    status = clock_gettime(CLOCK_REALTIME, &start);
    data = map_input(argv[1], &stbuf);
    
    if (status == -1) {
        perror("Error getting starting time");
        exit(EXIT_FAILURE);
    }

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

    status = clock_gettime(CLOCK_REALTIME, &end);
    if (status == -1) {
        perror("Error getting ending time");
        exit(EXIT_FAILURE);
    }

    // Log resource usage
    struct rusage resource;
    status = getrusage(RUSAGE_SELF, &resource);
    if (status == -1) {
        perror("Error getting resource usage");
        exit(EXIT_FAILURE);
    }

    log_perf(&start, &end, &resource);

    return 0;
}
