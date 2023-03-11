//
// Created by jordan on 06/03/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "../conf.h"
#include "../headers/utils/Coordinates.h"
#include "../headers/StateMachine.h"
#include "../headers/Map.h"
#include "../headers/Player.h"
#include "../headers/Trap.h"
#include "../headers/getch.h"


/** Possible states of the system **/
typedef enum {ST_FORGET = 0, ST_INIT, ST_ACQ, ST_MOVE_TOP, ST_MOVE_BOT, ST_MOVE_LEFT, ST_MOVE_RIGHT, ST_CHECK_WIN,
              ST_END_GAME, NB_STATES} state_t;

/** Possible inputs of the system **/
typedef enum {NOT_VALID = 0, CMD_TOP, CMD_BOT, CMD_LEFT, CMD_RIGHT, NEXT, WIN, LOSE , PLAY_AGAIN,
              GAME_OVER, NB_INPUTS} input_t;

/** Possible actions of the system **/
typedef enum {A_NO_ACTION = 0, A_INIT, A_MOVE_TOP, A_MOVE_BOT, A_MOVE_LEFT, A_MOVE_RIGHT, A_CHECK_WIN,
              A_END_GAME, A_GAME_OVER, NB_ACTIONS} action_t;

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
                [ST_CHECK_WIN][WIN]         = {ST_END_GAME, A_END_GAME},
                [ST_END_GAME][PLAY_AGAIN]   = {ST_INIT, A_INIT},

                [ST_CHECK_WIN][GAME_OVER]         = {ST_END_GAME, A_GAME_OVER}
                };


/**
 * @brief   Change state and perform actions according to a current state and an input
 * @param   input
 */
static void process_input(input_t input);

/**
 * @brief   Perform an action
 * @param   action The action to perform
 */
static void perform_action(action_t action);

/**
 * @brief Manage a player movement
 * @param c The caracter representing the move to do (ZQSD)
 */
static void manage_move(char c);

/**
 * @brief   Ask the player if he wants to play again
 */
static void play_again();

static state_t current_state;
static int nb_moves;
static Player *player;
static Trap *traps[NB_TRAPS];

void SM_init(){
    current_state = ST_ACQ;
    nb_moves = 0;

    // Init Player
    player = Player_init();

    // Init Treasure
    Treasure_init();

    // Init Map
    Map_init();

    for (int i = 0; i < NB_TRAPS; ++i) {
        traps[i] = Trap_init();
    }

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

void SM_free(){
    Player_free_all();
    Trap_free_all();
    Map_free();

    free(player);
    free(traps);
}


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
            printf(" ");

            // Check if the player walked on a trap
            Coordinates player_coords = Player_get_pos(player);
            for (int i = 0; i < NB_TRAPS; ++i) {
                Coordinates trap_coords = Trap_get_pos(traps[i]);
                if(player_coords.i == trap_coords.i && player_coords.j == trap_coords.j){
                    Player_lose_hp(player, 1);
                    Map_set_case(TRAP_ICON, trap_coords);

                    // Check if the player is now dead
                    if(Player_is_dead(player)){
                        process_input(GAME_OVER);
                    }
                }
            }

            Coordinates treasure_coords = Treasure_get_pos();
            bool is_win = player_coords.i == treasure_coords.i && player_coords.j == treasure_coords.j;

            if(is_win){
                process_input(WIN);
            }
            else{
                process_input(LOSE);
            }

            break;

        case A_END_GAME:
            printf("\nCongratulation, you found the treasure !\n");
            play_again();
            break;

        case A_GAME_OVER:
            printf("\nGame over !\n");
            play_again();
            break;

        default:
            break;
    }
}

static void manage_move(char c){
    nb_moves += 1;

    Coordinates old_coords = Player_get_pos(player);
    if(!Player_move(player, c)){
        process_input(NOT_VALID);
    }
    else{
        Map_set_case(EMPTY_CASE_ICON, old_coords);
        Map_set_case(PLAYER_ICON, Player_get_pos(player));
        system("clear");
        Map_print();
        printf("HP : %d\n", Player_get_hp(player));
        printf("Number of moves : %d\n", nb_moves);

        process_input(NEXT);
    }
}

static void play_again(){
    char resp;
    printf("Do you want to play again ? (y/n)");
    while (resp != 'y' && resp != 'n'){
        scanf("%c", &resp);
    }

    if(resp == 'y'){
        process_input(PLAY_AGAIN);
    }
    else{
        printf("Good bye !");
        SM_free();
    }

}