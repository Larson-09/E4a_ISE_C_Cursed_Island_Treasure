//
// Created by jordan on 10/03/23.
//

#include <stdlib.h>
#include "../headers/Trap.h"

struct Trap_t
{
    Coordinates coords;
};


Trap* Trap_init(void){
    Coordinates coords = Coordinates_generate_random_coords(NB_GRID_ROWS, NB_GRID_COLS);
    Trap *this = malloc(sizeof(Trap));
    this->coords = coords;

    return this;
}

Coordinates Trap_get_pos(Trap *this){
    return this->coords;
}

void Trap_free(Trap *this){
    free(this);
}