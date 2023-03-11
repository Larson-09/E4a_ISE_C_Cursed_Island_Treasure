//
// Created by jordan on 10/03/23.
//

#include <stdlib.h>
#include <time.h>
#include "../headers/Trap.h"

struct Trap_t
{
    Coordinates coords;
};

static Trap *instances[NB_TRAPS];
static int nb_instances;

Trap* Trap_init(void){
    Coordinates coords = Coordinates_generate_random_coords(NB_GRID_ROWS, NB_GRID_COLS);
    nb_instances = 0;
    Trap *this = malloc(sizeof(Trap));
    this->coords = coords;

    instances[nb_instances] = this;
    nb_instances ++;

    return this;
}

Coordinates Trap_get_pos(Trap *this){
    return this->coords;
}

void Trap_free_all(){
    for (int i = 0; i < nb_instances; ++i) {
        free(instances[i]);
    }
}