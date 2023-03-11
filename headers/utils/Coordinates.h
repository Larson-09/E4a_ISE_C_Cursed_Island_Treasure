//
// Created by jordan on 03/03/23.
//

#ifndef PROJET_ILE_MAUDITE_COORDINATES_H
#define PROJET_ILE_MAUDITE_COORDINATES_H
#include <time.h>
#include <stdbool.h>
#include "../../conf.h"

typedef struct {
    int i;
    int j;
}Coordinates;

/**
 * @brief   Generate a random coordinates (i, j)
 * @param   max_i   The maximum value of i
 * @param   max_j   THe maximum value of j
 * @return  The random coordinates
 */
Coordinates Coordinates_generate_random_coords(int max_i, int max_j);

/**
 * @brief   Check if 2 coordinates are equals
 * @param   c1  First coordinates
 * @param   c2  Second coordinates
 * @return  True if the coordinates are equals
 */
bool Coordinates_are_equals(Coordinates c1, Coordinates c2);

#endif //PROJET_ILE_MAUDITE_COORDINATES_H
