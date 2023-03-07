//
// Created by jordan on 06/03/23.
//
#include <stdio.h>
#include <stdlib.h>
#include "../conf.h"
#include "../headers/utils/Coordinates.h"
#include "../headers/StateMachine.h"
#include "../headers/Map.h"
#include "../headers/Treasure.h"
#include "../headers/Player.h"
#include "../headers/getch.h"


/** Possible states of the system **/
typedef enum {ST_FORGET = 0, ST_INIT, ST_ACQ, ST_MOVE_TOP, ST_MOVE_BOT, ST_MOVE_LEFT, ST_MOVE_RIGHT, ST_CHECK_WIN,
              NB_STATES} state_t;

/** Possible inputs of the system **/
typedef enum {NOT_VALID = 0, CMD_TOP, CMD_BOT, CMD_LEFT, CMD_RIGHT, NEXT, WIN, LOSE , NB_INPUTS} input_t;

/** Possible actions of the system **/
typedef enum {A_NO_ACTION = 0, A_INIT, A_MOVE_TOP, A_MOVE_BOT, A_MOVE_LEFT, A_MOVE_RIGHT, A_CHECK_WIN, NB_ACTIONS} action_t;

/** Transitions between states according to inputs **/
typedef struct {
    state_t target_state;
    action_t action;
} transition_t;

/** [INITIAL_STATE][INPUT] = [TARGET_STATE, ACTION] **/
static transition_t tab_transition [NB_STATES][NB_INPUTS] =
        {
                [ST_ACQ][CMD_TOP]           = {ST_MOVE_TOP, A_MOVE_TOP},
                [ST_ACQ][CMD_BOT]           = {ST_MOVE_BOT, A_MOVE_BOT},
                [ST_ACQ][CMD_LEFT]          = {ST_MOVE_LEFT, A_MOVE_LEFT},
                [ST_ACQ][CMD_RIGHT]         = {ST_MOVE_RIGHT, A_MOVE_RIGHT},

                [ST_MOVE_TOP][NEXT]         = {ST_CHECK_WIN, A_CHECK_WIN},
                [ST_MOVE_BOT][NEXT]         = {ST_CHECK_WIN, A_CHECK_WIN},
                [ST_MOVE_LEFT][NEXT]        = {ST_CHECK_WIN, A_CHECK_WIN},
                [ST_MOVE_RIGHT][NEXT]       = {ST_CHECK_WIN, A_CHECK_WIN},

                [ST_MOVE_TOP][NOT_VALID]    = {ST_ACQ, A_NO_ACTION},
                [ST_MOVE_BOT][NOT_VALID]    = {ST_ACQ, A_NO_ACTION},
                [ST_MOVE_LEFT][NOT_VALID]   = {ST_ACQ, A_NO_ACTION},
                [ST_MOVE_RIGHT][NOT_VALID]  = {ST_ACQ, A_NO_ACTION},

                [ST_CHECK_WIN][LOSE]         = {ST_ACQ, A_NO_ACTION},
                [ST_CHECK_WIN][WIN]         = {ST_INIT, A_INIT},

                };



/** Private functions **/
static void process_input(input_t input);
static void perform_action(action_t action);
static void manage_move(char c);

static state_t current_state;
static Player *player;

void SM_init(){
    current_state = ST_ACQ;
    player = Player_init();
    Treasure_init();

    Map_init();
    Map_set_case(TREASURE_ICON, Treasure_get_pos());
    Map_set_case(PLAYER_ICON, Player_get_pos(player));
    Map_print();
}

void SM_input_top(){
    process_input(CMD_TOP);
}

void SM_input_bot(){
    process_input(CMD_BOT);
}

void SM_input_left(){
    process_input(CMD_LEFT);
}

void SM_input_right(){
    process_input(CMD_RIGHT);
}

/**
 * @brief   Change state and perform actions according to a current state and an input
 * @param   input
 */
static void process_input(input_t input)
{
    transition_t tr_to_do;
    tr_to_do = tab_transition[current_state][input];

    if(tr_to_do.target_state != ST_FORGET) {
        current_state = tr_to_do.target_state;
        perform_action(tr_to_do.action);
    }
}

static void perform_action(action_t action)
{
    switch (action)
    {
        case A_NO_ACTION:
            break;

        case A_INIT:
            SM_init();
            break;

        case A_MOVE_TOP:
            manage_move(HOTKEY_TOP);
            break;

        case A_MOVE_BOT:
            manage_move(HOTKEY_BOT);
            break;

        case A_MOVE_LEFT:
            manage_move(HOTKEY_LEFT);
            break;

        case A_MOVE_RIGHT:
            manage_move(HOTKEY_RIGHT);
            break;

        case A_CHECK_WIN:
            printf("\0");
            Coordinates player_coords = Player_get_pos(player);
            Coordinates treasure_coords = Treasure_get_pos();
            bool is_win = player_coords.i == treasure_coords.i && player_coords.j == treasure_coords.j;

            if(is_win){
                process_input(WIN);
            }
            else{
                process_input(LOSE);
            }

            break;

        default:
            break;
    }
}

void manage_move(char c){
    Coordinates old_coords = Player_get_pos(player);
    if(!Player_move(player, c)){
        process_input(NOT_VALID);
    }
    else{
        Map_set_case(EMPTY_CASE_ICON, old_coords);
        Map_set_case(PLAYER_ICON, Player_get_pos(player));
        system("clear");
        Map_print();

        process_input(NEXT);
    }
}