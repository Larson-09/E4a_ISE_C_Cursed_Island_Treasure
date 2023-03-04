//
// Created by jordan on 03/03/23.
//

#include <stdlib.h>
#include <time.h>
#include "../conf.h"
#include "../headers/Treasure.h"

static Coordinates coords;

void Treasure_init(){
    srand(time(NULL));
    int i = rand() % (NB_GRID_ROWS + 1);
    int j  = rand() % (NB_GRID_COLS + 1);

    coords.i = i;
    coords.j = j;
}

Coordinates Treasure_get_pos(){
    return coords;
}