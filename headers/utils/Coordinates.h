//
// Created by jordan on 03/03/23.
//

#ifndef PROJET_ILE_MAUDITE_COORDINATES_H
#define PROJET_ILE_MAUDITE_COORDINATES_H
#include <time.h>
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

#endif //PROJET_ILE_MAUDITE_COORDINATES_H
