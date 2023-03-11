cmake_minimum_required(VERSION 3.24)
project(Projet_Ile_Maudite C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet_Ile_Maudite
        ../main.c
        ../headers/Player.h
        ../headers/Map.h
        ../headers/Treasure.h
        ../sources/Player.c
        ../sources/Map.c
        ../sources/Treasure.c
        ../sources/Trap.c
        ../headers/Treasure.h
        ../headers/utils/Coordinates.h
        ../headers/utils/Direction.h
        ../conf.h
        ../sources/getch.c
        ../headers/getch.h
        ../headers/StateMachine.h
        ../sources/StateMachine.c
        ../headers/utils/Coordinates.c ../sources/Trap.c)