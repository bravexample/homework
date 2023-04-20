// A header for map
#ifndef MAP_H
#define MAP_H

// Macro for the size of the map
#define MAP_WIDTH 25
#define MAP_HEIGHT 27
// Macro for the number of areas
#define AREA_NUM 19

// Libraries
#include <stdlib.h>
#include <time.h>

// For debugging
#include <stdio.h>

// enum for the items in the map
typedef
enum
{
    nothing = 0,
    Hills,
    Forest,
    Mountains,
    Fields,
    Pastures,
    Desert,
    Harbor_Any,
    Harbor_Brick,
    Harbor_Lumber,
    Harbor_Ore,
    Harbor_Grain,
    Harbor_Wool,
    Road,
    Village,
    City
}
MAP_ITEM;

// The map
MAP_ITEM** map = NULL;

// Function to fill the area into the map
static inline void fill_area_of_the_map(MAP_ITEM** map, MAP_ITEM area, int x, int y)
{
    // Initialize x and y
    x = (y > 3 ? y - 3 : 3 - y) * 2 + (x - 1) * 4 + 3;
    y = (y - 1) * 4 + 4;

    // Fill the area into the map
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            map[x + i][y + j] = area;
}

// Function to initialize the map
static inline void init_map()
{
    // Prepare the area array to be randomly assigned
    MAP_ITEM area[AREA_NUM] = 
    {
        Forest, Forest, Forest, Forest,
        Pastures, Pastures, Pastures, Pastures,
        Fields, Fields, Fields, Fields,
        Hills, Hills, Hills,
        Mountains, Mountains, Mountains,
        Desert
    };

    // Randomly rearrange the area array
    srand(time(NULL));
    for (int i = 0; i < AREA_NUM; i++)
    {
        int j = rand() % AREA_NUM;
        MAP_ITEM temp = area[i];
        area[i] = area[j];
        area[j] = temp;
    }

    // Allocate the map
    map = (MAP_ITEM**)malloc(sizeof(MAP_ITEM*) * MAP_WIDTH);
    for (int i = 0; i < MAP_WIDTH; i++)
        map[i] = (MAP_ITEM*)calloc(sizeof(MAP_ITEM), MAP_HEIGHT);

    // Assign the area array to the map
    for (int i = 0; i < AREA_NUM;)
    {
        for (int j = 1; j <= 5; j++)
        {
            // Area space of the line
            int space = 5 + (j > 3 ? 3 - j : j - 3);
            for (int k = 1; k <= space; k++)
                fill_area_of_the_map(map, area[i++], k, j);
        }
    }

    // Bulid Harbor
    map[7][2] = map[7][24] = map[13][24] = map[23][13] = Harbor_Any;
    map[3][17] = Harbor_Brick;
    map[3][9] = Harbor_Lumber;
    map[21][7] = Harbor_Ore;
    map[13][2] = Harbor_Grain;
    map[20][19] = Harbor_Wool;
}

// Print the map for debugging
static inline void print_map()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
            printf("%d ", map[j][i]);
        printf("\n");
    }
}

#endif