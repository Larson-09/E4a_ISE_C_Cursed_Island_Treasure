//
// Created by jordan on 03/03/23.
//

#ifndef PROJET_ILE_MAUDITE_MAP_H
#define PROJET_ILE_MAUDITE_MAP_H

#include "utils/Coordinates.h"

/**
 * @brief   Initialize the Map arguments
 */
void Map_init();

/**
 * @brief   Display the grid of the Map
 */
void Map_print();

char Map_get_case(Coordinates coords);

/**
 * @brief   Set the content of a case
 * @param   content     The content to put
 * @param   coords      The coordinates of the case to set
 */
void Map_set_case(char content, Coordinates coords);

#endif //PROJET_ILE_MAUDITE_MAP_H
