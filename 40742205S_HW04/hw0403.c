// a program of five-letter words guessed by the user

// includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// macro for length of a string
#define LEN 10

// main
int main(void) {
    // grep five-letter words from a dictionary file
    if (system("grep -E '^[a-z]{5}$' /usr/share/dict/american-english > hw0403_data/dict") < 0) {
        perror("grep dictionary failed");
        return 1;
    }

    // count the number of five-letter words
    int n = 0;
    // let file pointer be local variable
    {
        if (system("wc -l hw0403_data/dict > hw0403_data/n") < 0) {
            perror("wc dictionary failed");
            return 1;
        }
        FILE *fp = fopen("hw0403_data/n", "rb");
        if (fp == NULL) {
            perror("fopen file n failed");
            return 1;
        }
        if (fscanf(fp, "%d", &n) < 0) {
            perror("fscanf file n failed");
            return 1;
        }
        fclose(fp);
    }

    // set the seed of random number generator
    srand(time(NULL));
    // array for answer
    char answer[LEN];
    // loop to read five-letter words from dictionary file
    {
        FILE *fp = fopen("hw0403_data/dict", "rb");
        if (fp == NULL) {
            perror("fopen file dict failed");
            return 1;
        }
        // loop to read five-letter words from dictionary file
        while (1) {
            // randomly select a five-letter word
            int r = rand() % n;
            // skip r lines
            char temp[LEN];
            for (int i = 0; i < r; i++) {
                if (fgets(temp, LEN, fp) == NULL) {
                    perror("failed searching the answer");
                    return 1;
                }
            }
            // read five-letter word
            if (fgets(answer, LEN, fp) == NULL) {
                perror("fgets answer failed");
                return 1;
            }
            // remove newline character
            answer[5] = '\0';
            // check the word is valid
            int valid = 1;
            for (int i = 0; answer[i] != '\0'; i++) {
                if (answer[i] < 'a' || answer[i] > 'z') {
                    valid = 0;
                    break;
                }
            }
            // break the loop if the word is valid
            if (valid) {
                break;
            }
        }
        
        printf("Answer: %s\n", answer);
        fclose(fp);
    }

    // loop for user input
    for (int i = 0; i < 6; i++) {
        printf("Guess %d: ", i + 1);
        // read user input
        char guess[LEN];
        if (fgets(guess, LEN, stdin) == NULL) {
            perror("fgets guess failed");
            return 1;
        }
        // remove newline character
        guess[5] = '\0';
        // compare the guess with the answer
        char checked[LEN] = {0};
        char result[LEN] = {0};
        char check_result = 0;
        // check for correct letter and position
        for (int j = 0; j < 5; j++) {
            if (guess[j] == answer[j]) {
                checked[j] = 1;
                result[j] = 3;
                check_result++;
            }
        }
        if (check_result == 5) {
            // print the string with green color
            printf("\033[32m%s\033[0m\n", guess);
            printf("Congratulations\n");
            return 0;
        }
        // check for correct letter but not position
        for (int j = 0; j < 5; j++) {
            if (result[j] != 3) {
                for (int k = 0; k < 5; k++) {
                    if (answer[k] == guess[j]) {
                        if (checked[k] != 1) {
                            checked[k] = 1;
                            result[j] = 2;
                            break;
                        }
                        else {
                            result[j] = 1;
                        }
                    }
                }
            }
            // print the character according to the result
            switch (result[j]) {
            case 0:
                // print the character with white color
                printf("\033[37m%c\033[0m", guess[j]);
                break;
            case 1:
                // print the character with gray color
                printf("\033[30m%c\033[0m", guess[j]);
                break;
            case 2:
                // print the character with yellow color
                printf("\033[33m%c\033[0m", guess[j]);
                break;
            case 3:
                // print the character with green color
                printf("\033[32m%c\033[0m", guess[j]);
            }
        }
        // newline
        printf("\n");
    }

    // if the user fails to guess the answer
    printf("Good Luck\n");
    // exit
    return 0;
}