#include "util.h"

/* Read an input file and map it to program memory.
 * path: The relative or absolute input file path
 */
void *map_input(char *path, struct stat *stbuf) {
    int status, fd;
    void *data = NULL;
    // Open the file to get a file descriptor.
    if ((fd = open(path, O_RDONLY)) == -1) {
        return NULL;
    }
    // Stat the file for its size.
    if ((status = fstat(fd, stbuf)) == -1) {
        close(fd);
        return NULL;
    }
    // Mmap the file to memory for fast access.
    data = mmap(NULL, stbuf->st_size , PROT_READ, MAP_SHARED | MAP_POPULATE, fd, 0);
    // Close the file since we don't need the descriptor anymore.
    if ((status = close(fd)) == -1) {
        return NULL;
    }
    return data;
}

/* Split input data by newline-separated lines.
 * The input file must end with an empty line for this to work properly.
 * data: The raw text provided by the input file
 * len: The number of characters in the input file
 * n_lines: A pointer to the  number of newline-separated lines in 
 *          the input file. Updated by this function.
 */
char **split_by_line(char *data, size_t len, size_t *n_lines) {
    char **lines = NULL;
    char *str, *line, *saveptr;
    int i;

    // We need a copy because input data is read-only
    char *copy = malloc(len+1);
    memcpy(copy, data, len);

    // First pass is to count number of lines
    for (i = 0; i < len; i++) {
        if (data[i] == '\n') {
            *n_lines += 1;
        }
    }

    lines = malloc((*n_lines) * sizeof(char *));

    // Copy each line into the output
    for (i = 0, str = copy; ; i++, str = NULL) {
        line = strtok_r(str, "\n", &saveptr);
        if (line == NULL) {
            break;
        }
        lines[i] = malloc(strlen(line) + 1);
        strcpy(lines[i], line);
    }

    free(copy);
    return lines;
}

/* Parse lines into (integral) numbers.
 */
long *convert_input_to_long(char **lines, size_t n_lines) {
    long *numbers = malloc(n_lines * sizeof(int));
    for (int i = 0; i < n_lines; i++) {
        numbers[i] = atol(lines[i]);
    }
    return numbers;
}