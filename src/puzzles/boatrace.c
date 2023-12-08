/* This is my solution to day 6 of AOC 2023.
*/
#include "util.h"

/* This problem was much simpler than the others so far.
 * We have a toy boat and use it in a race.
 * We can charge the boat by holding down a button for
 * some time, and that gives it speed for the remaining time.
 * 
 * We win the race if the boat reaches a specified distance.
 * This gives us a quadratic equation x*(time-x) = distance
 * to solve for each race.
 * 
 * Part 1 gives us a list of races, and part 2 combines the digits
 * into a single race with large parameters.
 */
void calculate_wins(char **lines, size_t n_lines) {
    long p1_wins = 1, p2_wins = 0; 

    char *delims[3] = {":", " ", ""};
    parse_t *parse_tree = parse_string(lines[0], delims, 3);
    int n_times = 0;
    long *time = long_array_from_parse(parse_tree->children + 1, &n_times);
    char *buf = malloc(strlen(parse_tree->children[1].str));
    buf[0] = 0;
    for (int i = 0; i < n_times; i++) {
        strcat(buf, parse_tree->children[1].children[i].str);
    }
    long kerned_time = atol(buf);
    free(buf);
    free_parse_tree(parse_tree);

    parse_tree = parse_string(lines[1], delims, 3);
    int n_distances = 0;
    long *dist = long_array_from_parse(parse_tree->children + 1, &n_distances);
    buf = malloc(strlen(parse_tree->children[1].str));
    buf[0] = 0;
    for (int i = 0; i < n_distances; i++) {
        strcat(buf, parse_tree->children[1].children[i].str);
    }
    long kerned_dist = atol(buf);
    free(buf);
    free_parse_tree(parse_tree);

    for (int i = 0; i < n_times; i++) {
        double r1, r2;
        // solve x*(time-x)-dist = 0 
        // --> -x^2 + time*x - dist = 0
        // I added a small number to the distance in case the 
        // actual roots are integers, because exactly
        // matching the distance does not count as a win.
        solve_quadratic(-1, time[i], -dist[i]-1e-3, &r1, &r2);
        p1_wins *= (long)(r1) - (long)(r2+1) + 1;
    }

    double r1, r2;
    solve_quadratic(-1, kerned_time, -kerned_dist-1e3, &r1, &r2);
    p2_wins = ((long)r1-(long)r2);

    printf("The result for part 1 is : %ld\n", p1_wins);
    printf("The result for part 2 is : %ld\n", p2_wins);
}

void solve(void *data, size_t len) {
    size_t n_lines = 0;
    char **lines = split_by_line(data, len, &n_lines);
    calculate_wins(lines, n_lines);
    // Cleanup
    for (int i = 0; i < n_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}
