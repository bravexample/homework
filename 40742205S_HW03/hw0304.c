// A program to change the file in JINYONG game

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cheat.h"

// Some constants
#define MAX_PATH_LEN 4096

// Main
int32_t main(void) {
    // Get the path of file
    printf("Enter the path of file: ");
    uint8_t path[MAX_PATH_LEN];
    if (!fgets(path, MAX_PATH_LEN, stdin)) {
        perror("fgets");
        return 1;
    }
    path[strlen(path) - 1] = '\0';

    // Get the file to change
    int32_t file_num;
    while (1) {
        printf("Enter the file to change (1 to 3, 0 to exit): ");
        if (!scanf("%d", &file_num)) {
            printf("Invalid number!\n");
            continue;
        }

        if (!file_num)
            return 0;

        if (file_num >= 1 && file_num <= 3)
            break;
        
        printf("Invalid number!\n");
    }
    // Add filename after path
    sprintf(path + strlen(path), "/R%d.GRP", file_num);
    // Try to open the file
    FILE *fp = fopen(path, "rb+");
    if (!fp) {
        printf("Path you inputed: %s\n", path);
        perror("fopen");
        return 1;
    }

    // Let user choose what to do
    while (1) {
        // Clean terminal with printf
        printf("\033[2J\033[H");

        // Print the menu
        printf("Choose an option to do:\n");
        printf("\t0. Exit\n");
        printf("\t1. Maximize attributes\n");
        printf("\t2. Maximize items\n");
        printf("\t3. Maximize arts\n");
        printf("\t4. Change data by position of file (Don't use this option if you don't know WTF are you doing)\n");
        printf("Your choice: ");

        // Get the option
        int32_t choice;
        if (!scanf("%d", &choice)) {
            perror("");
            continue;
        }

        // Clear screen
        printf("\033[2J\033[H");

        // Options
        switch (choice) {
        case 0:
            // Exit
            return 0;
        case 1:
            // Maximize attributes
            ChangeAttributes(fp);
            break;
        case 2:
            // Maximize items
            ChangeItems(fp);
            break;
        case 3:
            // Maximize arts
            ChangeArts(fp);
            break;
        case 4:
            // Change data by position of file
            ChangeData(fp);
            break;
        default:
            getchar();
            printf("Invalid input!\n");
            // Wait for user to press enter
            printf("Press enter to continue...");
            getchar();
        }
    }

    // Exit
    return 0;
}