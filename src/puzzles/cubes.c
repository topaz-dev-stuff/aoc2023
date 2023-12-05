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
    char *colors[3] = {"red", "green", "blue"};
    int lengths[3] = {3, 5, 4};
    int limits[3] = {12, 13, 14};

    for (int i = 0; i < n_lines; i++) {
        char valid = 1;
        int max_pulls[3] = {0, 0, 0};
        char *delim[4] = {":", ";", ",", ""};
        parse_t *parse_tree = parse_string(lines[i], delim, 4);
        parse_t *pulls = parse_tree->children + 1;

        // Go through each set of cubes pulled per game,
        // and record the max number of cubes pulled of each
        // color type for the current game.
        for (int pull = 0; pull < pulls->n_children; pull++) {
            printf("%s\n", pulls->children[pull].str);
            parse_t *cubes = pulls->children + pull;
            for (int cube = 0; cube < cubes->n_children; cube++) {
                int number;
                char color[8];
                sscanf(cubes->children[cube].str, "%d %s", &number, color);
                printf("%s\t%d %s\n", cubes->children[cube].str, number, color);
                for (int c = 0; c < 3; c++) {
                    if (!strncmp(color, colors[c], lengths[c])) {
                        if (number > max_pulls[c]) {
                            max_pulls[c] = number;
                        }
                    }
                }
            }
        }

        // Part 1: Determine validity by checking the max pulls
        // against the hard limits. Add to the running total if
        // it is valid.
        for (int j = 0; j < 3; j++) {
            if (max_pulls[j] > limits[j]) {
                valid = 0;
            }
        }
        if (valid) {
            p1_sum += i+1;
        }

        // Part 2: Multiply the max pulls of each color together
        // and add the the running total.
        long power = 1;
        for (int j = 0; j < 3; j++) {
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
