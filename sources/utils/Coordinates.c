//
// Created by jordan on 10/03/23.
//
#include "../../headers/utils/Coordinates.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

static bool is_timer_set = false;

Coordinates Coordinates_create_coordinates(int i, int j){
    Coordinates coords;
    coords.i = i;
    coords.j = j;

    return coords;
}

Coordinates Coordinates_generate_random_coords(int max_i, int max_j){

    if(!is_timer_set){
        srand(time(NULL));
        is_timer_set = true;
    }


    int i = rand() % (max_i);
    int j  = rand() % (max_j);

    // Coordinates *coords = malloc(sizeof(Coordinates));
    Coordinates coords;
    coords.i = i;
    coords.j = j;

    return coords;
}

bool Coordinates_are_equals(Coordinates c1, Coordinates c2){
    return c1.i == c2.i && c1.j == c2.j;
}
