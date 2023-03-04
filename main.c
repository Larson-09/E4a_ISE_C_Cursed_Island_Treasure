#include <stdio.h>
#include "headers/Player.h"
#include "headers/Treasure.h"
#include "headers/Map.h"
#include "headers/getch.h"

static bool is_game_finished(Player *player);
static Direction char_to_direction(char c);

int main() {

    Player *player = Player_init();
    Map_init();
    Map_set_case(PLAYER_ICON, Player_get_pos(player));


    do{
        Map_print();
        // CLear previous player position
        Map_set_case(EMPTY_CASE_ICON, Player_get_pos(player));

        // Ask for player move
        bool is_move_ok;
        do{
            char c = getch();
            is_move_ok = Player_move(player, c);
        } while (!is_move_ok);

        // Add new player position to the grid
        Map_set_case(PLAYER_ICON, Player_get_pos(player));


    } while (!is_game_finished(player));

    printf("This is win !");
    return 0;
}

static bool is_game_finished(Player *player){
    Coordinates player_coords = Player_get_pos(player);
    Coordinates treasure_coords = Treasure_get_pos();
    return player_coords.i == treasure_coords.i && player_coords.j == treasure_coords.j;
}
