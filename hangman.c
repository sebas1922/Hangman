#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LIVES 6

// Function prototypes
char get_guess(char guesses[], int guesses_size);
bool val_guess(char guess, char guesses[], int guesses_size);
void draw(int guess_num, char word[]);
bool update_usrword(char usr_word[], char goal_word[], char guess);

int main() {
    // Take guess from player 1 to determine the goal_word player 2 will be guessing
    char goal_word[100] = "";
    printf("Player 1, pick a goal word: ");
    scanf("%s", goal_word);

    // Create the user goal_word that will be compared to the chosen goal_word, will start off as just underscores
    char usr_word[strlen(goal_word) + 1];  // Include space for null terminator
    for (int i = 0; i < strlen(goal_word); i++) {
        usr_word[i] = '_';
    }
    usr_word[strlen(goal_word)] = '\0';  // Null-terminate the string

    printf("Player 2, You have %d lives.\n", MAX_LIVES);

    // Set up array that will keep track of guesses already used by user
    char guesses[50] = "~";  // Initialize guesses array
    int guesses_size = 1;  // We start with one used guess, '~'

    // Game loop, ends if number of guesses is exceeded or usr_word equals goal_word
    int count = 0;
    while (strcmp(goal_word, usr_word)) {
        printf("%s\n", usr_word);
        
        // Check to see if number of guesses has been exceeded
        if (count >= MAX_LIVES) {
            printf("Word was: %s\nYou lose. Better luck next time!\n", goal_word);
            return 0;
        }

        printf("Lives remaining: %d\n", MAX_LIVES - count);
        
        // Get a valid guess
        char guess = get_guess(guesses, guesses_size);

        // Add guess to list of already guessed letters
        guesses[guesses_size++] = guess;

        // Update the user's word
        if (!update_usrword(usr_word, goal_word, guess)) {
            printf("%c is not in the word!\n", guess);
            count++;
        } else {
            printf("Nice guess!\n");
        }
    }

    printf("%s\nYou win!\n", usr_word);
    return 0;
}

// Draw hangman based on the number of guesses
void draw(int guess_num, char word[]) {
    printf("%s\n", word);
}

// Update the user word based on the guess
bool update_usrword(char usr_word[], char goal_word[], char guess) {
    bool changed = false;
    for (int i = 0; i < strlen(goal_word); i++) {
        if (goal_word[i] == guess) {
            usr_word[i] = guess;
            changed = true;
        }
    }
    return changed;
}

// Check to see whether or not the guess has already been guessed
bool val_guess(char guess, char guesses[], int guesses_size) {
    for (int i = 0; i < guesses_size; i++) {
        if (guess == guesses[i]) {
            return false;
        }
    }
    return true;
}

// Validates user input to be only 1 character and not already in guess list
char get_guess(char guesses[], int guesses_size) {
    while (true) {
        printf("Guess: ");
        
        // Clear the input buffer by consuming the newline character
        while (getchar() != '\n');  // Consume any leftover characters in the buffer
        
        // Read a valid character from the user
        char guess;
        
        // Read the first character, ensuring that we don't capture unwanted spaces or newlines
        while (scanf("%c", &guess) == 1) {
            // If the character is not a newline or a space, we consider it valid
            if (guess != ' ' && guess != '\n') {
                break;  // We got a valid character, exit the loop
            }
        }
        
        // Check if the guess is valid and has not been guessed already
        if (val_guess(guess, guesses, guesses_size)) {
            return guess;  // Valid guess, return it
        } else {
            // If the guess is invalid, print an error message
            printf("Invalid guess, please enter exactly one character that you haven't already guessed.\n");
        }
    }
}
