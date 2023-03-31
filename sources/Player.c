//
// Created by jordan on 03/03/23.
//
#include <stdlib.h>
#include "../headers/Player.h"

struct Player_t
{
    Coordinates coords;
    int hp;
};


static void Player_reset(Player *this);

Player *Player_init(void){

    Player* this;
    this = malloc(sizeof(Player));
    Player_reset(this);

    return this;
}

bool Player_move(Player *this, char direction){
    int next_i = this->coords.i;
    int next_j = this->coords.j;

    switch (direction) {
        case HOTKEY_TOP:
            next_i -= 1;
            break;
        case HOTKEY_BOT:
            next_i += 1;
            break;
        case HOTKEY_RIGHT:
            next_j += 1;
            break;
        case HOTKEY_LEFT:
            next_j -= 1;
            break;
        default:
            break;
    }

    if(next_i < 0 || next_i > (NB_GRID_ROWS -1) || next_j < 0 || next_j > (NB_GRID_COLS -1)){
        return false;
    }
    else{
        Coordinates *coords = &this->coords;
        coords->i = next_i;
        coords->j = next_j;
        return true;
    }
}

Coordinates Player_get_pos(Player *this){
    return this->coords;
}

Coordinates Player_set_pos(Player *this, Coordinates coords){
    this->coords = coords;
}

int Player_get_hp(Player *this){
    return this->hp;
}

void Player_lose_hp(Player *this, int nb_hp){
    this->hp -= nb_hp;
}

bool Player_is_dead(Player *this){
    return this->hp ==0;
}

void Player_free(Player *this){
    free(this);
}


static void Player_reset(Player *this)
{
    this->hp = PLAYER_NB_HP;
    Coordinates* p_coords = &this->coords;
    p_coords->i = 0;
    p_coords->j = 0;
}
