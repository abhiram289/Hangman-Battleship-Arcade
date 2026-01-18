/*
-------------------------------------------------------------
TEAM-08 : GAME ARCADE
-------------------------------------------------------------

TEAM MEMBERS:
M NAGA SAI ABHIRAM - PES1UG24AM151
MRINMAYI RAMAN - PES1UG24CS278
NEEL RAO - PES1UG24EC130
SHIVAKUMAR KUMBAR - PES1UG24EE043
-------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>  // provides access to the func tolower() used.

#define MAX_WORDS 10
#define MAX_GUESSES 6
#define SIZE 6

const char *words[MAX_WORDS] = {
    "plant", "cloud", "knife", "grape", "flame",
    "chalk", "drill", "stone", "brush", "flood"
};
const char *clues[MAX_WORDS] = {
    "A living thing that grows in soil",
    "Visible mass of condensed moisture in the sky",
    "A sharp tool used for cutting",
    "Small fruit used to make wine",
    "Burning gas from a fire",
    "Chemically, it's mostly calcium carbonate",
    "Tool used to make holes",
    "Hard solid mineral matter",
    "Tool used for painting or grooming",
    "Overflow of water onto land"
};

const char *hangmanPics[MAX_GUESSES + 1] = {
    "  +---+  \n  |   |  \n      |  \n      |  \n      |  \n      |  \n=========",
    "  +---+  \n  |   |  \n  O   |  \n      |  \n      |  \n      |  \n=========",
    "  +---+  \n  |   |  \n  O   |  \n  |   |  \n      |  \n      |  \n=========",
    "  +---+  \n  |   |  \n  O   |  \n /|   |  \n      |  \n      |  \n=========",
    "  +---+  \n  |   |  \n  O   |  \n /|\\  |  \n      |  \n      |  \n=========",
    "  +---+  \n  |   |  \n  O   |  \n /|\\  |  \n /    |  \n      |  \n=========",
    "  +---+  \n  |   |  \n  O   |  \n /|\\  |  \n / \\  |  \n      |  \n========="
};

void drawHangman(int wrongGuesses) {
    printf("%s\n", hangmanPics[wrongGuesses]);  // each time screen is refreshed and counter increases, the hangman is drawn
}

void playHangman(int *score) {  // score ptr updates the score if won
    srand((unsigned int)time(NULL));  // ensures no repetition of a word each run
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') { 
        int index = rand() % MAX_WORDS;
        const char *selectedWord = words[index];
        const char *selectedClue = clues[index];
        int wordLen = strlen(selectedWord);  // gets word length

        char displayWord[6];
        for (int i = 0; i < wordLen; i++) {
            displayWord[i] = '_';    // displays '_ _ _ _ _'
        }
        displayWord[wordLen] = '\0'; // of the 6 chars one is a '\0'

        int wrongGuesses = 0;  // no of wrong guesses
        int correctCount = 0;  // counts no of correct times 
        int totalUnique = 0;   // 
        int letterCount[26] = {0};

        for (int i = 0; i < wordLen; i++) {  // loops through word and counts unique letters and saves it
            int idx = selectedWord[i] - 'a';
            if (letterCount[idx] == 0) totalUnique++;
            letterCount[idx]++;
        }

        int guessed[26] = {0};  

       

        while (wrongGuesses < MAX_GUESSES && correctCount < totalUnique) {  // main loop
            system("@cls||clear"); // clears the terminal
            printf("\n========== HANGMAN BY TEAM-08 ==========\n");
            printf("Clue: %s\n\n", selectedClue);  // prints clue
            drawHangman(wrongGuesses); 

            printf("Word: ");
            for (int i = 0; i < wordLen; i++) {
                printf("%c ", displayWord[i]);
            }
            printf("\n");

            printf("Enter a letter: ");
            char guess;
            scanf(" %c", &guess);
            guess = tolower(guess);  // converts to lowercase if entered in uppercase

            if (guess < 'a' || guess > 'z') {
                printf("Invalid input. Please enter a letter.\n\n");
                continue;
            }
            if (guessed[guess - 'a']) {
                printf("You already guessed '%c'. Try another.\n\n", guess);
                continue;
            }

            guessed[guess - 'a'] = 1;  // guessed letter is marked so it wont be accepted again

            if (letterCount[guess - 'a'] > 0) {
                for (int i = 0; i < wordLen; i++) {
                    if (selectedWord[i] == guess) {
                        displayWord[i] = guess;
                    }
                }
                correctCount++;   //
                printf("Nice! '%c' is correct.\n\n", guess);  // prints if guessed letter is correct
            } else {
                wrongGuesses++;
                printf("Nope! '%c' is not in the word. %d guesses left.\n\n", guess, MAX_GUESSES - wrongGuesses);
            }

            printf("Press Enter to continue...");
            while (getchar() != '\n');
            getchar();
        }

        system("@cls||clear");
        drawHangman(wrongGuesses);

        // wrongGuesses < MAX_GUESSES	Player can keep guessing
        // correctCount < totalUnique	Not all letters found yet
        // correctCount == totalUnique	Player wins
        // wrongGuesses == MAX_GUESSES	Player loses

        if (correctCount == totalUnique) { 
            printf(" You guessed it! The word was '%s'. You win!\n", selectedWord);
            (*score)++;  // the scoreboard is updated 
        } else {
            printf(" You lost. The word was '%s'. Better luck next time!\n", selectedWord);
        }

        printf("\nDo you want to play Hangman again? (y/n): ");
        scanf(" %c", &playAgain); 
    }
}

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = '-';
}

void printBoard(char board[SIZE][SIZE]) {
    printf("   ");
    for (int i = 0; i < SIZE; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d  ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void playBattleship(int *score) {
    char board[SIZE][SIZE];
    int shipRow, shipCol;
    int guessRow, guessCol;
    char playAgain;

    srand(time(NULL));

    do {
        initializeBoard(board);
        shipRow = rand() % SIZE;
        shipCol = rand() % SIZE;

        printf("\n=== Welcome to Battleship ===\n");
        printf("Guess the location of the hidden ship (%dx%d grid)!\n", SIZE, SIZE);

        while (1) {
            printBoard(board);

            int validInput = 0;
            while (!validInput) {
                printf("Enter row (0-%d): ", SIZE - 1);
                if (scanf("%d", &guessRow) != 1 || guessRow < 0 || guessRow >= SIZE) {
                    printf("Invalid row input!\n");
                    while (getchar() != '\n');
                    continue;
                }

                printf("Enter column (0-%d): ", SIZE - 1);
                if (scanf("%d", &guessCol) != 1 || guessCol < 0 || guessCol >= SIZE) {
                    printf("Invalid column input!\n");
                    while (getchar() != '\n');
                    continue;
                }

                validInput = 1;
            }

            if (guessRow == shipRow && guessCol == shipCol) {
                board[guessRow][guessCol] = 'X';
                printBoard(board);
                printf(" You hit the ship! You win!\n");
                (*score)++;
                break;
            } else {
                if (board[guessRow][guessCol] == 'O') {
                    printf(" You already guessed this spot.\n");
                } else {
                    board[guessRow][guessCol] = 'O';
                    printf(" Miss! Try again.\n");
                }
            }
        }

        printf("Do you want to play Battleship again? (y/n): ");
        scanf(" %c", &playAgain);
        while (getchar() != '\n');

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("Thanks for playing Battleship!\n");
}

int main() {
    int choice;
    int hangmanScore = 0;
    int battleshipScore = 0;

    do {
        system("@cls||clear");

        printf("\n");
        printf("  ==========================================\n");
        printf("  ||                                      ||\n");
        printf("  ||          WELCOME TO TEAM-08's        ||\n");
        printf("  ||             GAME ARCADE              ||\n");
        printf("  ||                                      ||\n");
        printf("  ==========================================\n");
        printf("  ||                                      ||\n");
        printf("  ||  1. Play HANGMAN                     ||\n");
        printf("  ||  2. Play BATTLESHIP                  ||\n");
        printf("  ||  3. Exit                             ||\n");
        printf("  ||                                      ||\n");
        printf("  ==========================================\n");
        printf("  ||                                      ||\n");
        printf("  ||               SCOREBOARD             ||\n");
        printf("  ||                                      ||\n");
        printf("  ||        Hangman Wins    : %-3d         ||\n", hangmanScore);
        printf("  ||        Battleship Wins : %-3d         ||\n", battleshipScore);
        printf("  ||                                      ||\n");
        printf("  ==========================================\n");

        printf("\n  Enter your choice (1-3): ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                playHangman(&hangmanScore);
                break;
            case 2:
                playBattleship(&battleshipScore);
                break;
            case 3:
                printf("\n  Thank you for playing!\n");
                printf("  Final Scores:\n");
                printf("  - Hangman Wins    : %d\n", hangmanScore);
                printf("  - Battleship Wins : %d\n", battleshipScore);
                break;
            default:
                printf("\n  Invalid choice. Please select 1, 2, or 3.\n");
        }

        if (choice != 3) {
            printf("\n  Press Enter to return to the menu...");
            getchar();
        }

    } while (choice != 3);

    return 0;
}