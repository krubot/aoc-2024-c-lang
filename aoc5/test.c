#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PAGES 100
#define MAX_UPDATES 100

// Function to check if the pages are in the correct order based on constraints
bool is_order_correct(int *update, int update_size, int **constraints, int num_constraints) {
    for (int i = 0; i < num_constraints; i++) {
        int page_a = constraints[i][0];
        int page_b = constraints[i][1];
        int pos_a = -1, pos_b = -1;

        // Find the positions of page_a and page_b in the update
        for (int j = 0; j < update_size; j++) {
            if (update[j] == page_a) pos_a = j;
            if (update[j] == page_b) pos_b = j;
        }

        // If page_a or page_b is missing in the update, skip the check for this rule
        if (pos_a == -1 || pos_b == -1) continue;

        // If page_a is not before page_b, return false
        if (pos_a > pos_b) return false;
    }
    return true;
}

// Function to calculate the middle page number of the update
int calculate_middle_page(int *update, int update_size) {
    return update[update_size / 2];
}

// Comparison function for integers used in qsort
int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Main function to solve the problem
int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    int constraints[MAX_PAGES][2];
    int num_constraints = 0;

    // Read the page ordering rules
    while (fscanf(file, "%d|%d\n", &constraints[num_constraints][0], &constraints[num_constraints][1]) != EOF) {
        num_constraints++;
    }

    // Skip the empty line between constraints and the list of updates
    char ch;
    while ((ch = fgetc(file)) != '\n' && ch != EOF);

    int updates[MAX_UPDATES][MAX_PAGES];
    int update_sizes[MAX_UPDATES];
    int num_updates = 0;

    // Read the updates (list of pages)
    while (fscanf(file, "%d", &updates[num_updates][0]) != EOF) {
        int page;
        int update_size = 1;

        // Read the pages for the current update
        while ((ch = fgetc(file)) != '\n' && ch != EOF) {
            if (ch == ',') {
                fscanf(file, "%d", &page);
                updates[num_updates][update_size++] = page;
            }
        }
        update_sizes[num_updates] = update_size;
        num_updates++;
    }

    // Part 1: Calculate the sum of middle page numbers for correct updates
    int correct_sum = 0;
    for (int i = 0; i < num_updates; i++) {
        if (is_order_correct(updates[i], update_sizes[i], constraints, num_constraints)) {
            correct_sum += calculate_middle_page(updates[i], update_sizes[i]);
        }
    }

    printf("Part 1: Sum of middle pages for correctly ordered updates: %d\n", correct_sum);

    // Part 2: Fix the incorrect updates and calculate the sum of middle page numbers for the corrected updates
    int corrected_sum = 0;
    for (int i = 0; i < num_updates; i++) {
        if (!is_order_correct(updates[i], update_sizes[i], constraints, num_constraints)) {
            // Sort the pages to fix the order (use qsort)
            qsort(updates[i], update_sizes[i], sizeof(int), compare_ints);
            corrected_sum += calculate_middle_page(updates[i], update_sizes[i]);
        }
    }

    printf("Part 2: Sum of middle pages for corrected updates: %d\n", corrected_sum);

    fclose(file);
    return 0;
}

