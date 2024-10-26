cmake_minimum_required(VERSION 3.29)
project(ing1_smestre1_info C)

set(CMAKE_C_STANDARD 11)

add_executable(ing1_smestre1_info main.c
        ../menu.h
        ../menu.c
        ../joueur.h
        ../joueur.c
        ../jeux.h
        ../jeux.c
        ../plateau.c
        ../plateau.h
        joueur.h)
