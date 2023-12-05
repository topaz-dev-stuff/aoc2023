#include "util.h"

char **split(char *str, char *delim, int *n_substrings) {
    int delim_count = 0;
    int delim_len = strlen(delim);
    int substring_start = 0;
    int i;

    for(i = 0; i < strlen(str) - delim_len; i++) {
        if (!strncmp(str + i, delim, delim_len)) {
            delim_count++;
        }
    }

    *n_substrings = delim_count + 1;
    if (!delim_count) {
        return NULL;
    }

    char **result = malloc(*n_substrings * sizeof(char *));
    delim_count = 0;
    for(i = 0; i < strlen(str) - delim_len; i++) {
        if (!strncmp(str + i, delim, delim_len)) {
            int len = i - substring_start;
            result[delim_count] = malloc(len + 1);
            strncpy(result[delim_count], str + substring_start, len);
            result[delim_count][len] = 0;
            substring_start = i + delim_len;
            delim_count++;
        }
    }

    int len = i - substring_start + 1;
    result[delim_count] = malloc(len + 1);
    strncpy(result[delim_count], str + substring_start, len);
    result[delim_count][len] = 0;

    return result;
}

/* Remove empty strings from an array.
 * Destroys the array strings and returns a newly
 * allocated array with an updated len.
 */
char **remove_empty_strings(char **strings, int *len) {
    int new_len = *len, idx = 0;
    char **result;

    for (int i = 0; i < *len; i++) {
        if (!strings[i][0]) {
            new_len--;
        }
    }

    result = malloc(new_len * sizeof(char *));
    for (int i = 0; i < *len; i++) {
        if (strings[i][0]) {
            result[idx] = malloc(strlen(strings[i]) + 1);
            strcpy(result[idx], strings[i]);
            idx++;
        }
        free(strings[i]);
    }
    free(strings);

    *len = new_len;
    return result;
}

void free_string_array(char **strings, int len) {
    for (int i = 0; i < len; i++) {
        free(strings[i]);
    }
    free(strings);
}



parse_t *parse_string(char *raw, char **delim, int n_delims) {
    if (!n_delims) {
        return NULL;
    }

    parse_t *root = malloc(sizeof(parse_t));
    int n_substrings = 0;
    root->str = malloc(strlen(raw) + 1);
    strcpy(root->str, raw);
    root->n_children = 0;
    root->children = NULL;
    
    char **split_string = split(raw, *delim, &n_substrings);

    if (split_string) {
        split_string = remove_empty_strings(split_string, &n_substrings);
        root->n_children = n_substrings;
        root->children = calloc(n_substrings, sizeof(parse_t));
        
        for (int i = 0; i < n_substrings; i++) {
            parse_t *child = parse_string(split_string[i], delim + 1, n_delims - 1);
            if (child) {
                memcpy(root->children + i, child, sizeof(parse_t));
                free(child);
            }
        }

        free_string_array(split_string, n_substrings);
    }
    
    return root;
}

void free_parse_tree(parse_t *root) {
    if (!root) {
        return;
    }

    for (int i = 0; i < root->n_children; i++) {
        free_parse_tree(root->children + i);
    }
    free(root->str);
    free(root->children);
}

int *int_array_from_parse(parse_t *node, int *len) {
    *len = node->n_children;
    int *result = malloc(node->n_children * sizeof(int));
    for(int i = 0; i < node->n_children; i++) {
        result[i] = atoi(node->children[i].str);
    }
    return result;
}

long *long_array_from_parse(parse_t *node, int *len) {
    *len = node->n_children;
    long *result = malloc(node->n_children * sizeof(long));
    for(int i = 0; i < node->n_children; i++) {
        result[i] = atol(node->children[i].str);
    }
    return result;
}
