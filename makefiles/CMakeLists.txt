cmake_minimum_required(VERSION 3.24)
project(Projet_Ile_Maudite C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet_Ile_Maudite ../main.c ../headers/Player.h ../headers/Map.h ../headers/Treasure.h ../sources/Player.c ../sources/Map.c ../sources/Treasure.c ../headers/utils/Coordinates.h ../headers/utils/Direction.h ../conf.h ../sources/getch.c ../headers/getch.h ../headers/Entity.h ../sources/Entity.c ../headers/StateMachine.h ../sources/StateMachine.c)
