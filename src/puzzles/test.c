/* This is a sample test file to ensure the runner program works.
 * It is also run as a default if no day is specified to the Makefile.
 */

#include "util.h"

void part1 () {
    printf("Hello, ");
}

void part2 () {
    printf("World!\n");
}

void solve (void *data, size_t len) {
    part1();
    part2();
    printf("%s\n", (char *)data);
}
