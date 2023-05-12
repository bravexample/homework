// Implementation of cheat.h

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cheat.h"

// Some constants
#define MAX_PATH_LEN 4096

// Offset of attributes
#define LEVEL   0x362
#define HP      0x366
#define STAMINA 0x36E
#define ETHIC   0x3B4
#define OTHERS  0x396
#define NUM_OTH 14
#define HIDDEN  0x3B8
#define NUM_HID 3
void ChangeAttributes(FILE *fp) {
    // An array for attributes
    uint8_t att[] = {0xFF, 0x7F};

    // Change level
    fseek(fp, LEVEL, SEEK_SET);
    fwrite(att, sizeof(uint8_t), 2, fp);

    // Change HP
    fseek(fp, HP, SEEK_SET);
    fwrite(att, sizeof(uint8_t), 2, fp); // HP Now
    fwrite(att, sizeof(uint8_t), 2, fp); // HP Max

    // Change stamina
    fseek(fp, STAMINA, SEEK_SET);
    fwrite(att, sizeof(uint8_t), 2, fp);

    // Change ethic
    fseek(fp, ETHIC, SEEK_SET);
    fwrite(att, sizeof(uint8_t), 2, fp);

    // Change others
    fseek(fp, OTHERS, SEEK_SET);
    for (uint32_t i = 0; i < NUM_OTH; i++)
        fwrite(att, sizeof(uint8_t), 2, fp);
    
    // Change hidden attributes
    fseek(fp, HIDDEN, SEEK_SET);
    for (uint32_t i = 0; i < NUM_HID; i++)
        fwrite(att, sizeof(uint8_t), 2, fp);
    
    // Output message
    printf("Attributes changed!\nPress enter to continue...");
    getchar(); getchar();
}

// Constants for items
#define ITEM_START 0x24
#define ITEM_CELL 0x4
#define ITEM_AMOUNT 0xC6
void ChangeItems(FILE *fp) {
    // Move file pointer to the start of items
    fseek(fp, ITEM_START, SEEK_SET);

    // An array for item
    uint8_t item[ITEM_CELL] = {0};
    // Set the amount of items to 0x7FFF
    item[2] = 0xFF;
    item[3] = 0x7F;
    // Write to file
    for (uint32_t i = 0; i < ITEM_AMOUNT; i++) {
        item[0] = i;
        fwrite(item, sizeof(uint8_t), ITEM_CELL, fp);
    }

    // Output message
    printf("Items changed!\nPress enter to continue...");
    getchar(); getchar();
}

// Constants for arts
#define ART_SPACE   10
#define ART_TYPE    0x5C
#define ART_START   0x3C2
#define ART_LEVEL   0x3d6
void ChangeArts(FILE *fp) {
    // Move file pointer to the start of arts
    fseek(fp, ART_START, SEEK_SET);

    // Cell for art
    uint8_t art[2] = {0};

    // Get the arts
    uint32_t i = 0;
    for (; i < ART_SPACE; i++) {
        // Get the type of art from user
        printf("Enter the type of art (0 to exit) (Hex): ");
        if (!scanf("%hhx", art)) {
            printf("Invalid number!\n");
            i--;
            continue;
        }

        // Exit if user input 0
        if (!art[0])
            break;
        
        // Check if the type is valid
        if (art[0] > ART_TYPE) {
            printf("Invalid type!\n");
            i--;
            continue;
        }
        
        // Write to file
        fwrite(art, sizeof(uint8_t), 2, fp);
    }

    // Move file pointer to the level of arts
    fseek(fp, ART_LEVEL, SEEK_SET);

    // Set the level of arts to 0x7FFF
    art[0] = 0xFF;
    art[1] = 0x7F;
    for (uint32_t j = 0; j < i; j++)
        fwrite(art, sizeof(uint8_t), 2, fp);
    
    // Output message
    printf("Arts changed!\nPress enter to continue...");
    getchar(); getchar();
}

void ChangeData(FILE *fp) {
    // Get the offset of data
    uint32_t offset;
    printf("Enter the offset of data (Count from the start of file) (Hex): ");
    if (!scanf("%x", &offset)) {
        printf("Invalid number!\n");
        return;
    }

    // Move file pointer to the offset
    fseek(fp, offset, SEEK_SET);

    // Get the number of bytes to change
    uint32_t bytes;
    printf("Enter the number of bytes to change (Dec): ");
    if (!scanf("%d", &bytes)) {
        printf("Invalid number!\n");
        return;
    }

    // Get the new data and write to file
    for (uint32_t i = 0; i < bytes; i++) {
        uint8_t data;
        printf("Enter the new data (Hex): ");
        if (!scanf("%hhx", &data)) {
            printf("Invalid number!\n");
            return;
        }

        fwrite(&data, sizeof(uint8_t), 1, fp);
    }
}