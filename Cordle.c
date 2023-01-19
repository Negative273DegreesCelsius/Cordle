#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * @brief Checks if a character is in a given word
 * 
 * @param character the character to look for
 * @param pos the index of the character in the guess
 * @param word the word to be checked
 * @return int 0 if character is not in the word, 1 if it is in another position, 2 if it is in the same position
 */
int checkForChar(char character, int pos, char *word) {
    if (word[pos] == character) {
        return 2;
    } else {
        for (int i = 0; i < 5; i++) {
            if (word[i] == character) return 1;
        }
    }
    return 0;
}

/**
 * @brief Checks if 2 strings match (containing same characters until it reachs \0)
 * 
 * @param str1 the first string
 * @param str2 the second string
 * @return true if the strings match
 * @return false if the strings don't match
 */
bool checkStrings(char *str1, char *str2) {
    int i = 0;
    while ((str1[i] != '\0') && (str2[i] != '\0')) {
        if (str1[i] != str2[i]) return false;
        i++;
    }
    return true;
}

int main() {
    FILE *file;
    file = fopen("five-letter-words.txt", "r");

    int line = 0;
    char word[10];
    char currentWord[10];

    srand(time(NULL));

    // get random word
    int count = 0;
    while (fgets(currentWord, sizeof(currentWord), file) != NULL)
    {
        count++;
        if (rand() / (float) RAND_MAX <= (1.0 / count)) strcpy(word, currentWord);
    }
    word[5] = '\0';

    char answer[5];
    for (int i = 0; i <= 5; i++) {
        answer[i] = word[i];
    }

    int guesses = 6;

    while (guesses > 0) {
        printf("Guesses remaining: %d\n", guesses);
        char guess[5];
        printf("Enter a word: ");
        scanf("%s", &guess);
        guess[5] = '\0';
        printf("%s\n", guess);
        for (int i = 0; i <= 5; i++) {
            answer[i] = word[i];
        }
        if (checkStrings(guess, answer)) {
            printf("You guessed the word! The word was %s ", answer);
            return 0;
        }
        for (int i = 0; i < 5; i++) {
            switch (checkForChar(guess[i], i, answer)) {
                case 0:
                    printf("_");
                    break;
                case 1:
                    printf("%c", guess[i]);
                    break;
                case 2:
                    printf("%c", toupper(guess[i]));
                    break;

            }
        }
        printf("\n\n");
        guesses--;
    }

    printf("You ran out of guesses. The word is %s ", answer);

    return 0;
}