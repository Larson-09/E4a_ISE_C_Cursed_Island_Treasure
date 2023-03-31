//
// Created by jordan on 03/03/23.
//

#ifndef PROJET_ILE_MAUDITE_TREASURE_H
#define PROJET_ILE_MAUDITE_TREASURE_H

#include "utils/Coordinates.h"

/**
 * @brief   Initialize the treasure
 */
void Treasure_init();

/**
 * @brief   Return the position of the Treasure
 * @return  The coordinates of the player position
 */
Coordinates Treasure_get_pos();

/**
 * @brief   Free all memory
 */
void Treasure_free();

#endif //PROJET_ILE_MAUDITE_TREASURE_H
