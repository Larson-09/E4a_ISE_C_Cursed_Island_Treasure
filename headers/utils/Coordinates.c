//
// Created by jordan on 10/03/23.
//
#include "Coordinates.h"
#include <stdlib.h>
#include <time.h>

Coordinates Coordinates_generate_random_coords(int max_i, int max_j){
    srand(time(NULL));
    int i = rand() % (NB_GRID_ROWS);
    int j  = rand() % (NB_GRID_COLS);

    Coordinates *coords;
    coords->i = i;
    coords->j = j;
}
