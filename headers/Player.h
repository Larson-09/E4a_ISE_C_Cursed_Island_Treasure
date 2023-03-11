//
// Created by jordan on 03/03/23.
//

#ifndef PROJET_ILE_MAUDITE_PLAYER_H
#define PROJET_ILE_MAUDITE_PLAYER_H

#include <stdbool.h>
#include "../conf.h"
#include "utils/Coordinates.h"
#include "utils/Direction.h"

typedef struct Player_t Player;

/**
 * @brief Initialize the arguments of the player
 * @return A pointer on the struct containing the arguments
 */
Player* Player_init(void);

/**
 * @brief Move the player to a given direction
 * @param   this        The pointer of the struct containing the arguments
 * @param   direction   The direction toward which we want to move the player
 * @return  true if the move was authorized, else it returns false and the move is not canceled
 */
bool Player_move(Player *this, char direction);

/**
 * @brief   Returns the coordinates of the player current position
 * @param   this    A pointer on the struct containing the arguments of the Player
 * @return  The coordinates of the player current position
 */
Coordinates Player_get_pos(Player *this);

#endif //PROJET_ILE_MAUDITE_PLAYER_H

/**
 * @brief   Returns the number of health points of the player
 * @param   this    The player
 * @return  Number of health points of the player
 */
int Player_get_hp(Player *this);

/**
 * @brief   Retrieve some health points from the player
 */
void Player_lose_hp(Player *this, int nb_hp);

/**
 * @brief   Check if the player is dead (0 hp)
 * @param   this    The player
 * @return  True if the player is dead
 */
bool Player_is_dead(Player *this);

/**
 * @brief   Free all Player instances memory
 */
void Player_free_all();


