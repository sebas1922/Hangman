#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_GUESSES 6

//see if user usr_word is valid
char get_guess(int, char[]);

bool val_guess(char, char[]);

void draw(int, char[]);


int main(){
    //take guess from player 1 to determine the goal_word player 2 will be guessing
    char goal_word[100] = "";
    printf("Player 1, pick a goal word: ");
    scanf("%s", goal_word);

    //create the user goal_word that will be compared to the chosen goal_word, will start off as just underscores
    char usr_word[strlen(goal_word)];
    for(int i=0; i<strlen(goal_word); i++){
        usr_word[i] = '_';
    }
    
    printf("Player 2, You have %d guesses.\n", MAX_GUESSES);

    //set up array that will keep track of guesses already used by user
    char guesses[7];
    int guesses_size = 0;
    
    /*
    game loop
    game ends if number of guesses is exceeded or users goal_word equals goal goal_word
    */
    int count = 1;
    while(strcmp(goal_word, usr_word)){
        draw(count, usr_word);
        //check to see if number of guesses has been exceeded
        if(count >= MAX_GUESSES){
            printf("You lose get good\n");
            return 0;
        }
        
        //get a valid guess
        char guess = get_guess(count, guesses);

        //add guess to list of already guessed letters
        guesses[guesses_size++] = guess;

        count++;
        printf("loop %d\n", count);
    }

    printf("You win!\n");
    return 0;
} 

//draw hangman based on number of guesses
void draw(int guess_num, char word[]){
    printf("%s\n", word);
}

bool val_guess(char guess, char guesses[]){
    for(int i=0; i<strlen(guesses); i++){

        if(guess == guesses[i]){
            printf("shits false\n");
            return false;
        }
    }

    return true;
}


//validates user input to be only 1 character and not already in guess list
char get_guess(int count, char guesses[]){
    while (true) {
        printf("Guess %d: \n", count);
        
        // Use scanf to read a character
        char guess = scanf("%c", &guess);
        
        // Check if the guess is a single character and not in guess_list
        if (guess == 1 && getchar() == '\n' && val_guess(guess, guesses)) {  // Check if exactly one character is guess
            // Valid single character guess
            return guess;
        } else {
            // If more than one character is entered, clear the guess buffer
            while (getchar() != '\n'); // Clear the buffer
            printf("Invalid guess, please enter exactly one character that you haven't already.\n");
        }
    }
}
