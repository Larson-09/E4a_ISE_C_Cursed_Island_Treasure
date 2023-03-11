//
// Created by jordan on 03/03/23.
//
#include <stdlib.h>
#include <stdio.h>
#include "../headers/Map.h"

static char **grid;

void Map_init(){

    // Memory allocation
    grid = (char **) malloc(NB_GRID_ROWS * sizeof(char *));
    for (int i = 0; i < NB_GRID_ROWS; i++) {
        grid[i] = (char *)malloc(NB_GRID_COLS * sizeof(char));
    }

    // Fill the grid
    for(int i=0; i< NB_GRID_ROWS; i++)
    {
        for(int j=0; j<NB_GRID_COLS; j++)
        {
            grid[i][j] = ' ';
        }
    }
}

void Map_print(){

    printf("\n CURSED ISLAND TREASURE \n \n");

    // Add treasure
    Coordinates treasure_coords = Treasure_get_pos();
    Map_set_case(TREASURE_ICON, treasure_coords);

    // Display empty grid
    for(int j= 0; j<NB_GRID_ROWS; j++)
    {
        for(int i=0; i<NB_GRID_COLS; i++)
        {
            printf("+---");
        }
        printf("+\n");
        //ligne de contenu
        for(int i=0; i<NB_GRID_COLS; i++)
        {
            printf("| ");
            printf("%c",grid[j][i]);
            printf(" ");
        }
        printf("|\n");
    }

    for(int i=0; i<NB_GRID_COLS; i++)
    {
        printf("+---");
    }
    printf("+\n");
}

char Map_get_case(Coordinates coords){
    return grid[coords.j][coords.j];
}

void Map_set_case(char content, Coordinates coords){
    grid[coords.i][coords.j] = content;
}

void Map_free(){
    free(grid);
}