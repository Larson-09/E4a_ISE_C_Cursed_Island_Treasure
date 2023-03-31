//
// Created by jordan on 03/03/23.
//

#include "../conf.h"
#include "../headers/Treasure.h"
#include <stdlib.h>
#include <time.h>

static Coordinates coords;

void Treasure_init(){
    coords = Coordinates_generate_random_coords(NB_GRID_ROWS, NB_GRID_COLS);
}

Coordinates Treasure_get_pos(){
    return coords;
}

void Treasure_free(){}

