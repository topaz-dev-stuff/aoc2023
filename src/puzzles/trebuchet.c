/* This is my solution to day 1 of AOC 2023.
 */

#include "util.h"

/* For this part, we were asked to scan through each string
 * and find the first and last numerical digit '1'-'9' to
 * get a two-digit result. The result from each string is
 * added to a running sum, which is reported at the end.
 */
void part1(char **data, size_t len) {
    long sum = 0;
    // Loop through each string
    for (int i = 0; i < len; i++) {
        char first, last, c;
        // Since -1 is not a value that can appear,
        // once we replace first's value,
        // we know not to set it again.
        first = -1;
        // Search the string for digits.
        for (int j = 0; j < strlen(data[i]); j++) {
            c = data[i][j];
            // All the number digits are next to each other
            // in the ASCII encoding, so we just need to make
            // sure the current character is between '0' and '9'
            // to know if it's a number, 
            // as opposed to checking all digits. 
            if (c >= '0' && c <= '9') {
                if (first == -1) {
                    first = c - '0';
                }
                last = c - '0';
            }
        }
        // The first digit is the 10's place and the last digit is the 1's
        // place, so multiply first by 10 and add them together to
        // get the actual number we're looking for.
        sum += (first * 10) + last;
    }
    printf("The answer to part 1 is %ld.\n", sum);
}

/* For part 2, we do the same thing as in part 1, but we now count
 * string representations of the digits (i.e. "one" in place '1').
 */
void part2(char **data, size_t len) {
    // These arrays keep track of the string representations
    // of the digits and their lengths.
    char *numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int lengths[9] = {3, 3, 5, 4, 4, 3, 5, 5, 4};
    long sum = 0;
    for (int i = 0; i < len; i++) {
        char first, last, c;
        first = -1;
        int cur_len = strlen(data[i]);
        for (int j = 0; j < cur_len; j++) {
            c = data[i][j];
            if (c >= '0' && c <= '9') {
                if (first == -1) {
                    first = c - '0';
                }
                last = c - '0';
            }
            // This is the main new code for this part,
            // we take a window 
            else {
                for (int k = 0; k < 9; k++) {
                    // Check that there's enough remaining length in the string
                    // and compare the two.
                    if (lengths[k] <= cur_len - j) {
                        if (!strncmp(numbers[k], data[i] + j, lengths[k])) {
                            if (first == -1) {
                                first = k+1;
                            }
                            last = k+1;
                            // None of the strings are substrings of each other,
                            // (i.e. we don't have both "eight" and "eighteen")
                            // so we can exit early here if we found a match.
                            break;
                        }
                    }
                }
            }
        }
        sum += (first * 10) + last;
    }
    printf("The answer to part 2 is %ld.\n", sum);
}

void solve(void *data, size_t len) {
    // Split the input into each line, and run each part in sequence.
    size_t n_lines = 0;
    char **lines = split_by_line(data, len, &n_lines);
    part1(lines, n_lines);
    part2(lines, n_lines);
    // Cleanup
    for (int i = 0; i < n_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}
