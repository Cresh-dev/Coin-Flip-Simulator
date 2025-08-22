/*
 * ========================================================================
 *  COIN FLIP SIMULATOR
 *  ----------------------------------------------------------------------
 *  Description:
 *    This program simulates coin flips and analyzes patterns of 
 *    consecutive outcomes. It provides functionality to:
 *      - Generate random flips
 *      - Display results
 *      - Calculate statistics for sequences of 5 consecutive heads or tails
 *
 *  Author:  Alessio Crescenzio
 *  Date:    22 August 2025
 *  Version: 1.0.0
 *
 *  Copyright (c) 2025 Alessio Crescenzio
 *  SPDX-License-Identifier: MIT
 * ========================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants
#define MAX_FLIPS 100000
#define MIN_FLIPS 1
#define SEQUENCE_LENGTH 5       
#define HEADS 0                 
#define TAILS 1
#define PAUSE_INTERVAL 20

static int *flip_results = NULL;    // Array to store flip results
static int num_flips = 0;   // Current number of flips performed

/* 
 * CLEAR INPUT BUFFER
 * ==================
 * Clears any leftover characters in the input buffer,
 * up to the next newline.
 */
void clear_input_buffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * PAUSE
 * =====
 * Pauses program execution until the user presses Enter.
 */
void pause(void) {
    printf("\nPress Enter to continue...\n");
    clear_input_buffer();
}

/*
 * GET_VALID_INPUT
 * ===============
 * Gets validated integer input from user within specified range.
 * Continues prompting until valid input is received.
 *
 * Parameters:
 *   min: Minimum acceptable value
 *   max: Maximum acceptable value
 *
 * Returns: Valid integer within the specified range
 */
int get_valid_input(int min, int max) {
    int input;
    while(1){
        if(scanf("%d", &input) != 1 || input < min || input > max){
            printf("Please enter a number between %d and %d: ", min, max);
        } else break;
        clear_input_buffer();
    }   
    clear_input_buffer();
    return input;
}

/*
 * DISPLAY_MENU
 * ============
 * Shows the main menu with all available options.
 */
void display_menu(void){
    printf("================ MAIN MENU ===============\n");
    printf("1 - Generate coin flips\n");
    printf("2 - Display flip results\n");
    printf("3 - Show pattern statistics\n");
    printf("0 - Exit program\n");
    printf("==========================================\n");
}

/*
 * GENERATE_FLIPS
 * =============
 * Asks how many throws we want to make. 
 * Generates values that can be 1 (tails) or 0 (heads). 
 */

int generate_flips(void){
    int requested_flips;

    printf("How many coin flips would you like to generate?\n");
    printf("(Range: %d - %d): ", MIN_FLIPS, MAX_FLIPS);

	requested_flips = get_valid_input(MIN_FLIPS, MAX_FLIPS);

    if(flip_results != NULL) {
        free(flip_results);
        flip_results = NULL;
    }

    flip_results = malloc(sizeof(int) * requested_flips);

    if (!flip_results) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < requested_flips; i++){
        flip_results[i] = rand() % 2;   // 0 = Heads, 1 = Tails
    }

    return requested_flips;
}

/*
 * FLIP_TO_STRING
 * ==============
 * Converts numeric flip value to human-readable string.
 *
 * Parameters:
 *   flip: value representing the flip (0 or 1)
 *
 * Returns: String representation of the flip
 */
char* flip_to_string(int flip) {
    if (flip == HEADS) return "HEADS";
    if (flip == TAILS) return "TAILS";
    return "UNKNOWN";   // Fallback in case of invalid value
}

/*
 * DISPLAY_FLIPS
 * =============
 * Shows all generated coin flip results in a formatted table.
 * Displays both numeric and text representation of flips.
 */
void display_flips(void){
	if(num_flips == 0) {
        printf("No flips have been generated yet.\n");
        return;
    }
    
	for(int i = 0; i < num_flips; i++) {
        printf("%6d  |   %d   | %s\n",
               i + 1,
               flip_results[i],
               flip_to_string(flip_results[i]));

        // Pause every 20 lines for better readability
        if((i + 1) % PAUSE_INTERVAL == 0 && i < num_flips - 1) pause();
    }

    printf("========================\n");
    printf("Total flips displayed: %d\n", num_flips);
}

/*
 * STATISTICS
 * ==========
 * Analyzes flip patterns and counts consecutive sequences.
 * Counts sequences of exactly SEQUENCE_LENGTH consecutive same results.
 */
void statistics(void){
    int heads_sequences = 0;
    int tails_sequences = 0;
    int current_heads_streak = 0;
    int current_tails_streak = 0;
    int total_heads = 0;
    int total_tails = 0;   
    
    if(num_flips == 0) {
        printf("No flips have been generated yet.\n");
        printf("Please use option 1 to generate flips first.\n");
        return;
    }

    for (int i = 0; i < num_flips; i++) {
        if (flip_results[i] == HEADS) {
            total_heads++;
            current_heads_streak++;
            current_tails_streak = 0;
            if (current_heads_streak == SEQUENCE_LENGTH) {
                heads_sequences++;
            }
        } else {
            total_tails++;
            current_tails_streak++;
            current_heads_streak = 0;
            if (current_tails_streak == SEQUENCE_LENGTH) {
                tails_sequences++;
            }
        }
    }

    printf("FLIP DISTRIBUTION:\n");
    printf("==================\n");
    printf("Total Heads: %d (%.1f%%)\n", total_heads,
           (double)total_heads / num_flips * 100);
    printf("Total Tails: %d (%.1f%%)\n", total_tails,
           (double)total_tails / num_flips * 100);

    printf("\nCONSECUTIVE SEQUENCE ANALYSIS:\n");
    printf("==============================\n");
    printf("Sequences of %d consecutive HEADS: %d\n", SEQUENCE_LENGTH, heads_sequences);
    printf("Sequences of %d consecutive TAILS: %d\n", SEQUENCE_LENGTH, tails_sequences);
    printf("Total consecutive sequences found: %d\n", heads_sequences + tails_sequences);
}

/*
 * CLEAR_SCREEN
 * ============
 * Clears the console screen using system-appropriate command.
 */
void clear_screen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(){
    srand((unsigned int)time(NULL));
    int choice;
	clear_screen();

    do{
        display_menu();
        printf("Enter your choice (0-3): ");
        choice = get_valid_input(0, 3);
        printf("\n");

		switch(choice){
			case 1: 
                num_flips = generate_flips(); 
                if(num_flips > 0) printf("\nSuccessfully generated %d coin flips!\n", num_flips);
                break;
			case 2: 
                display_flips(); 
                break;
			case 3: 
                statistics(); 
                break;
			case 0: 
                printf("Thank you for using the Coin Flip Simulator!\n"); 
                break;
            default:
                printf("Invalid choice. Please try again.\n");
		}
        if(choice != 0) {
            pause();
            clear_screen();
        }
	} while (choice != 0);

    if(flip_results) free(flip_results);

    return 0;
}
