/* This is my solution to day 5 of AOC 2023.
*/
#include "util.h"

typedef struct range {
    long start;
    long len;
    struct range *next;
    bool modified;
} range_t;

#define in_range(a,start,len) (a >= start && a < start + len)

/* Truncate range to be completely inside map_range,
 * and add the remainder into the list as a new range.
 */
void range_intersection(range_t *range, range_t *map_range) {
    if (in_range(range->start, map_range->start, map_range->len)) {
        // range falls entirely inside map_range, no need to split
        if (in_range(range->start + range->len - 1, map_range->start, map_range->len)) {
            return;
        }
        // only starting portion of the range is inside the map range
        else {
            range_t *end_range = malloc(sizeof(range_t));
            long overlap = map_range->len - (range->start - map_range->start);
            end_range->start = map_range->start + map_range->len;
            end_range->len = range->len - overlap;
            end_range->modified = false;
            end_range->next = range->next;

            range->len = overlap;
            range->next = end_range;
        }
    }
    // only ending portion of the range is inside the map range
    else if (in_range(range->start + range->len - 1, map_range->start, map_range->len)) {
        range_t *start_range = malloc(sizeof(range_t));
        long not_overlap = map_range->start - range->start;
        start_range->start = range->start;
        start_range->len = not_overlap;
        start_range->modified = false;
        start_range->next = range->next;

        range->start = map_range->start;
        range->len = range->len - not_overlap;
        range->next = start_range;
    }
    // map range is a subset of range
    else if (range->start < map_range->start 
             && range->start + range->len > map_range->start + map_range->len) {
        range_t *end_range = malloc(sizeof(range_t));
        end_range->start = map_range->start + map_range->len;
        end_range->len = (range->start + range->len) - (map_range->start + map_range->len);
        end_range->modified = false;
        end_range->next = range->next;

        range_t *start_range = malloc(sizeof(range_t));
        start_range->start = range->start;
        start_range->len = map_range->start - range->start;
        start_range->modified = false;
        start_range->next = end_range;

        range->start = map_range->start;
        range->len = map_range->len;
        range->next = start_range;
    }
}

/* Map the list of ranges into the next layer
 */
void map_ranges(range_t *head, range_t *map_range, long dest) {
    range_t *cur = head;

    while (cur) {
        if (cur->modified) {
            cur = cur->next;
            continue;
        }
        if (in_range(cur->start, map_range->start, map_range->len)
            || in_range(cur->start + cur->len - 1, map_range->start, map_range->len)
            || (cur->start < map_range->start 
            && cur->start + cur->len > map_range->start + map_range->len)) {
            range_intersection(cur, map_range);
            long diff = cur->start - map_range->start;
            cur->start = dest + diff;
            cur->modified = true;
        }
        cur = cur->next;
    }
}

/* This was really hard for only being day 5!
 * We have a bunch of numbers and a list of mappings to perform
 * on those numbers, and in the end we report the minimum
 * number. Part 2 gives us a very large (on the order of 1.8 billion)
 * set of numbers in the form of contiguous ranges, so we have to
 * be a bit more clever. To account for this, I just made
 * my part 1 solution work as ranges of length 1.
 */
void map_seeds(char **lines, size_t n_lines) {
    long p1_min = 1UL << 62, p2_min = 1UL << 62;
    char *delim[3] = {":", " ", ""};
    parse_t *original_seeds = parse_string(lines[0], delim, 3);
    int n_seeds;
    unsigned int *seeds = int_array_from_parse(original_seeds->children + 1, &n_seeds);
    free_parse_tree(original_seeds);
    free(original_seeds);

    range_t *p1_seeds = NULL, *p2_seeds = NULL, *cur = NULL, *prev = NULL;
    for (int i = 0; i < n_seeds; i++) {
        cur = malloc(sizeof(range_t));
        cur->start = seeds[i];
        cur->len = 1;
        cur->modified = false;
        cur->next = prev;
        prev = cur;
    }
    p1_seeds = cur;
    prev = NULL;
    for (int i = 0; i < n_seeds; i += 2) {
        cur = malloc(sizeof(range_t));
        cur->start = seeds[i];
        cur->len = seeds[i + 1];
        cur->modified = false;
        cur->next = prev;
        prev = cur;
    }
    p2_seeds = cur;

    for (int i = 2; i < n_lines; i++) {
        for (; i < n_lines; i++) {
            //signals a new kind of mapping
            if (lines[i][0] >= 'a' && lines[i][0] <= 'z') {
                break;
            }
            char *delims[2] = {" ", ""};
            parse_t *parse_tree = parse_string(lines[i], delims, 2);
            int n_nums;
            long *map = long_array_from_parse(parse_tree, &n_nums);
            free_parse_tree(parse_tree);
            free(parse_tree);
            range_t map_range;
            map_range.start = map[1];
            map_range.len = map[2];
            long dest = map[0];
            map_ranges(p1_seeds, &map_range, dest);
            map_ranges(p2_seeds, &map_range, dest);
            free(map);
        }
        cur = p1_seeds;
        while (cur) {
            cur->modified = false;
            cur = cur->next;
        }
        cur = p2_seeds;
        while (cur) {
            cur->modified = false;
            cur = cur->next;
        }
    }

    cur = p1_seeds;
    while (cur) {
        if (cur->start < p1_min) {
            p1_min = cur->start;
        }
        range_t *next = cur->next;
        free(cur);
        cur = next;
    }

    cur = p2_seeds;
    while (cur) {
        if (cur->start < p2_min) {
            p2_min = cur->start;
        }
        range_t *next = cur->next;
        free(cur);
        cur = next;
    }

    free(seeds);

    printf("The result for part 1 is : %ld\n", p1_min);
    printf("The result for part 2 is : %ld\n", p2_min);
}

void solve(void *data, size_t len) {
    size_t n_lines = 0;
    char **lines = split_by_line(data, len, &n_lines);
    map_seeds(lines, n_lines);
    // Cleanup
    for (int i = 0; i < n_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}
