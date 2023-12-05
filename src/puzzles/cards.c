/* This is my solution to day 4 of AOC 2023.
*/
#include "util.h"

/* This problem gave us some scratchcards with a set of 
 * winning numbers and the card's numbers.
 * 
 * In part 1, the score of the card is calculated as 2^(n-1),
 * where n is the number of numbers that match a winning number.
 * We find the matches and sum up the scores.
 * 
 * In part 2, we win more cards based on the number of matches:
 * card 1 having 1 match gives us 1 more of card 2, card 2 having 2
 * matches gives us a copy of cards 3 and 4 for each copy of card 2,
 * and so on. We need to figure out the total number of cards we
 * have at the end, and this is calculated by using a recurrence.
 */
void scratchcards(char **lines, size_t n_lines) {
    long p1_sum = 0, p2_sum = 0; 
    int i = 0;

    long total_cards[n_lines];
    for (i = 0; i < n_lines; i++) {
        total_cards[i] = 1;
    }

    for (i = 0; i < n_lines; i++) {
        int *winners, *cards, winning_len, card_len;

        char *delims[4] = {":", "|", " ", ""};
        parse_t *parse_tree = parse_string(lines[i], delims, 4);
        winners = int_array_from_parse(parse_tree->children[1].children, &winning_len);
        cards = int_array_from_parse(parse_tree->children[1].children + 1, &card_len);

        int this_winnings = 1, matches = 0;
        for (int card_idx = 0; card_idx < card_len; card_idx++) {
            for (int win_idx = 0; win_idx < winning_len; win_idx++) {
                if (cards[card_idx] == winners[win_idx]) {
                    matches++;
                    this_winnings <<= 1;
                    goto next;
                }
            }
next:
        }
        for (int match = 1; match <= matches; match++) {
            if (i + match < n_lines) {
                total_cards[i + match] += total_cards[i];
            }
        }
        this_winnings >>= 1;
        p1_sum += this_winnings;
        p2_sum += total_cards[i];
    }

    printf("The result for part 1 is : %ld\n", p1_sum);
    printf("The result for part 2 is : %ld\n", p2_sum);
}

void solve(void *data, size_t len) {
    size_t n_lines = 0;
    char **lines = split_by_line(data, len, &n_lines);
    scratchcards(lines, n_lines);
    // Cleanup
    for (int i = 0; i < n_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}
