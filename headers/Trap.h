//
// Created by jordan on 10/03/23.
//

#ifndef PROJET_ILE_MAUDITE_TRAP_H
#define PROJET_ILE_MAUDITE_TRAP_H

#include "utils/Coordinates.h"

typedef struct Trap_t Trap;

/**
 * @brief Initialize the arguments of the Trap
 * @return A pointer on the struct containing the arguments
 */
Trap* Trap_init(void);

/**
 * @brief
 * @return
 */
Coordinates Trap_get_pos(Trap *this);

/**
 * @brief   Free memory
 */
void Trap_free(Trap *this);

#endif //PROJET_ILE_MAUDITE_TRAP_H
