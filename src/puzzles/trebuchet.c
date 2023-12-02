/* This is my solution to day 1 of AOC 2023.
 */

#include "util.h"

/* For part 1, we were asked to scan through each string
 * and find the first and last numerical digit '1'-'9' to
 * get a two-digit result. The result from each string is
 * added to a running sum, which is reported at the end.
 * For part 2, we do the same thing as in part 1, but we now 
 * additionally count string representations of the digits 
 * (i.e. "one" in place of '1').
 * It was described as "calibrating" a trebuchet, hence the name.
 */
void calibrate(char **lines, size_t n_lines) {
    // These arrays keep track of the string representations
    // of the digits and their lengths.
    char *numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int lengths[9] = {3, 3, 5, 4, 4, 3, 5, 5, 4};
    long p1_sum = 0, p2_sum = 0;
    for (int i = 0; i < n_lines; i++) {
        char p1_first, p2_first, p1_last, p2_last, c;
        // Since -1 is not a value that can appear,
        // once we replace first's value,
        // we know not to set it again.
        p1_first = -1;
        p2_first = -1;
        // Search the string for digits.
        int cur_len = strlen(lines[i]);
        for (int j = 0; j < cur_len; j++) {
            // c is the current character
            c = lines[i][j];
            if (c >= '0' && c <= '9') {
                if (p1_first == -1) {
                    p1_first = c - '0';
                }
                if (p2_first == -1) {
                    p2_first = c - '0';
                }
                p1_last = c - '0';
                p2_last = c - '0';
            }
            // This is the main new code for this part,
            // we take a window 
            else {
                for (int k = 0; k < 9; k++) {
                    // Check that there's enough remaining length in the string
                    // and compare the two.
                    if (lengths[k] <= cur_len - j) {
                        if (!strncmp(numbers[k], lines[i] + j, lengths[k])) {
                            if (p2_first == -1) {
                                p2_first = k+1;
                            }
                            p2_last = k+1;
                            // None of the strings are substrings of each other,
                            // (i.e. we don't have both "eight" and "eighteen")
                            // so we can exit early here if we found a match.
                            break;
                        }
                    }
                }
            }
        }
        // Add to the running sum
        p1_sum += (p1_first * 10) + p1_last;
        p2_sum += (p2_first * 10) + p2_last;
    }
    printf("The answer to part 1 is %ld.\n", p1_sum);
    printf("The answer to part 2 is %ld.\n", p2_sum);
}

void solve(void *data, size_t len) {
    // Split the input into each line, and run each part in sequence.
    size_t n_lines = 0;
    char **lines = split_by_line(data, len, &n_lines);
    calibrate(lines, n_lines);
    // Cleanup
    for (int i = 0; i < n_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}
