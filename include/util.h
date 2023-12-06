/* Utility functions and universal includes for the project.
 */

#ifndef __UTIL__
#define __UTIL__

// Redundant definitions to get red squiggles to go away
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#endif // CLOCK_REALTIME
#ifndef CLOCK_PROCESS_CPUTIME_ID
#define CLOCK_PROCESS_CPUTIME_ID 2
#endif // CLOCK_PROCESS_CPUTIME_ID
#ifndef MAP_POPULATE
#define MAP_POPULATE 0x20000
#endif // MAP_POPULATE

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

// I/O functions
void *map_input(char *path, struct stat *stbuf);
char **split_by_line(char *data, size_t len, size_t *n_lines);

// Logging functions
void log_perf(struct timespec *start, struct timespec *end, struct rusage *rusage);

// Math functions
long logb2(size_t x);
long round_pow2_up(size_t x);

// String manipulation
char **split(char *str, char *delim, int *n_substrings);
char **remove_empty_strings(char **strings, int *len);
void free_string_array(char **strings, int len);

typedef struct parse_tree_node {
    char *str;
    struct parse_tree_node *children;
    int n_children;
} parse_t;

parse_t *parse_string(char *raw, char **delim, int n_delims);
void free_parse_tree(parse_t *root);
int *int_array_from_parse(parse_t *node, int *len);
long *long_array_from_parse(parse_t *node, int *len);

#endif // __UTIL__