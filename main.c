#include <stdio.h>
#include <stdlib.h>
#include "headers/Player.h"
#include "headers/StateMachine.h"
#include "headers/getch.h"

int main()
{
    char c;
    SM_init();

    while(1)
    {
        c = getch();
        switch (c)
        {
            case HOTKEY_TOP:
                SM_input_top();
                break;
            case HOTKEY_BOT:
                SM_input_bot();
                break;
            case HOTKEY_LEFT:
                SM_input_left();
                break;
            case HOTKEY_RIGHT:
                SM_input_right();
                break;
            case HOTKEY_EXIT:
                exit(0);
            default:
                break;
        }
    }

    return 0;
}