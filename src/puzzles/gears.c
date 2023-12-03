/* This is my solution to day 3 of AOC 2023.
 */
#include "util.h"

/* We have a matrix of characters, with many numbers
 * spelled out, and symbols placed nearby. Periods
 * represent empty space, and are to be ignored.
 * 
 * For part 1, we read all of the digits, with contiguous
 * digits being combined into a single number. Numbers
 * with a symbol touching any digit (including diagonally)
 * are added to a sum which is reported at the end.
 * 
 * For part 2, a "gear" (* symbol) with exactly two
 * numbers touching it is considered to be special,
 * and we need to multiply those two numbers together
 * to get a "gear ratio", and report the sum of all
 * such gear ratios.
 */
void parts_and_gears(char **lines, size_t n_lines) {
    long p1_sum = 0, p2_sum = 0;
    int line_size = strlen(lines[0]);

    // Mask tells us where the "gears" (*) are and how many
    // numbers are near them, and gear ratios will be the
    // product of all nearby numbers to a gear.
    char mask[n_lines][line_size];
    long gear_ratios[n_lines][line_size];

    // Initial state for mask and ratios.
    for (int i = 0; i < n_lines; i++) {
        for (int j = 0; j < line_size; j++) {
            mask[i][j] = 0;
            gear_ratios[i][j] = 1;
        }
    }

    // Go over each line.
    for (int i = 0; i < n_lines; i++) {
        char *cur_line = lines[i];
        int line_pos;
        // In each line, iterate across the line and search for a number.
        for (line_pos = 0; line_pos < line_size; line_pos++) {
            if (cur_line[line_pos] >= '0' && cur_line[line_pos] <= '9') {
                int length;
                // Find the number of digits in the number.
                for (length = 1; length < line_size - line_pos; length++) {
                    if (!(cur_line[line_pos + length] >= '0' && cur_line[line_pos + length] <= '9')) {
                        break;
                    }
                }

                // Convert ASCII form of number to an integer.
                char *num_str = malloc(length + 1);
                strncpy(num_str, cur_line + line_pos, length);
                num_str[length] = 0;

                int num = atoi(num_str);
                free(num_str);
                
                // Check to see if there is a symbol neighboring the
                // number in the input.
                char neighboring = 0;
                for (int j = i-1; j <= i + 1; j++) {
                    for (int k = line_pos-1; k <= line_pos + length; k++) {
                        if (j >= 0 && j < n_lines && k >= 0 && k < line_size) {
                            char c = lines[j][k];
                            if (c != '.' && !(c >= '0' && c <= '9')) {
                                neighboring = 1;
                            }
                            // If the symbol is a gear, add 1 to its count of nearby numbers
                            // and multiply its ratio by the number.
                            if (c == '*') {
                                mask[j][k] += 1;
                                gear_ratios[j][k] *= num;
                            }
                        }
                    }
                }
                // If the number is neighboring a symbol, add it to the total.
                if (neighboring) {
                    p1_sum += num;
                }
                line_pos += length;
            }
        }
    }

    // Find the sum of all gear ratios for gears
    // with two nearby numbers. We could technically
    // improve the complexity of this by using a
    // sparse matrix, but it wouldn't help anything
    // because the bulk of the program is still O(n^2). 
    for (int i = 0; i < n_lines; i++) {
        for (int j = 0; j < line_size; j++) {
            if (mask[i][j] == 2) {
                p2_sum += gear_ratios[i][j];
            }
        }
    }

    printf("The answer to part 1 is %ld.\n", p1_sum);
    printf("The answer to part 2 is %ld.\n", p2_sum);
}

void solve(void *data, size_t len) {
    // Split the input into each line, and run each part in sequence.
    size_t n_lines = 0;
    char **lines = split_by_line(data, len, &n_lines);
    parts_and_gears(lines, n_lines);
    // Cleanup
    for (int i = 0; i < n_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}