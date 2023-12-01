/* Utility functions and universal includes for the project.
 */

#ifndef __UTIL__
#define __UTIL__

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

void *map_input(char *path, struct stat *stbuf);
char **split_by_line(char *data, size_t len, size_t *n_lines);
long *convert_input_to_long(char **lines, size_t n_lines);

#endif // __UTIL__