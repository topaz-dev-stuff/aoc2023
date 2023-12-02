/* This is my solution to day 2 of AOC 2023.
*/
#include "util.h"

/* This is a text parsing nightmare in C.
 * Both parts entail pulling red, green, and/or blue cubes
 * out of a bag in separate pulls. Games are a single line of
 * input, with pulls being separated by semicolons.
 * Part 1 requires that we check that hard-coded cube limits are
 * not violated in order to call the game "valid", while part 2
 * requires keeping track of the minimum number of cubes required
 * to play the game as listed (throwing out the limits).
 * 
 * Both parts are solved by simply keeping track of the highest
 * number of cubes pulled of a certain type in a game,
 * with minor changes at the end to accomplish their specific task.
 */
void play_games(char **lines, size_t n_lines) {
    long p1_sum = 0, p2_sum = 0;
    char *strings[3] = {"red", "green", "blue"};
    int lengths[3] = {3, 5, 4};
    int limits[3] = {12, 13, 14};

    // Go through each game
    for (int i = 0; i < n_lines; i++) {
        char valid = 1;
        char *str1, *token1, *saveptr1;
        char *str2, *token2, *saveptr2;
        int j, k;
        int max_pulls[3] = {0, 0, 0};

        char *cur_line = lines[i];
        token1 = strtok_r(cur_line, ":", &saveptr1);
        printf("%s\n", token1);
        // We can arguably use i+1 for id, but the test writer
        // might hypothetically be mean and put games out of order >:(
        int id = atoi(token1 + 5);
        cur_line = strtok_r(NULL, ":", &saveptr1);
        printf("%s\n", cur_line);

        // Read the pulls
        for (j = 0, str1 = cur_line; ; j++, str1 = NULL) {
            token1 = strtok_r(str1, ";", &saveptr1);
            if (token1 == NULL) {
                break;
            }
            printf("%s\n", token1);

            // Read the cubes in each pull
            for (k = 0, str2 = token1; ; k++, str2 = NULL) {
                token2 = strtok_r(str2, ",", &saveptr2);
                if (token2 == NULL) {
                    break;
                }

                char *saveptr3; // throwaway
                int num = atoi(strtok_r(token2 + 1, " ", &saveptr3));
                char *color_id = strtok_r(NULL, " ", &saveptr3);

                // Match the cube's color and check if it is the new max
                // for that color of cube.
                for (int color = 0; color < 3; color++) {
                    if (strlen(color_id) <= lengths[color]) {
                        if (!strncmp(color_id, strings[color], lengths[color])) {
                            if (num > max_pulls[color]) {
                                max_pulls[color] = num;
                            }
                        }
                    }
                }
                token2 = saveptr2;
            }
            token1 = saveptr1;
        }

        // Part 1: Determine validity by checking the max pulls
        // against the hard limits. Add to the running total if
        // it is valid.
        for (j = 0; j < 3; j++) {
            if (max_pulls[j] > limits[j]) {
                valid = 0;
            }
        }
        if (valid) {
            p1_sum += id;
        }

        // Part 2: Multiply the max pulls of each color together
        // and add the the running total.
        long power = 1;
        for (j = 0; j < 3; j++) {
            power *= max_pulls[j];
        }
        p2_sum += power;
    }

    printf("The result for part 1 is : %ld\n", p1_sum);
    printf("The result for part 2 is : %ld\n", p2_sum);
}

void solve(void *data, size_t len) {
    // Split the input into each line, and run each part in sequence.
    size_t n_lines = 0;
    char **lines = split_by_line(data, len, &n_lines);
    play_games(lines, n_lines);
    // Cleanup
    for (int i = 0; i < n_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}
